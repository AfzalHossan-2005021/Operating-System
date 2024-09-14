#!/bin/bash

# Check if the file exists
if [ ! -f $2 ]; then
    echo "File does not exist: $2"
    exit 1
fi

# Check if the file is readable 
if [ ! -r $2 ]; then
    echo "File is not readable: $2"
    exit 1
fi

# Convert the input_file to unix format
dos2unix -q $2

# Create an array to store the lines
input_file=()
# Read each line into the array
while IFS= read -r line; do
    input_file+=("$line")  # Append each line to the array
done < "$2"

# Check whether the input file is in valid format
# Check if the file contains exactly 11 lines
if [ ${#input_file[@]} -ne 11 ]; then
    echo "The input file is in invalid format: File does not contain exactly 11 lines."
    exit 1
fi

# Check if the first line is valid
Is_Archive="${input_file[0]}"
if [ "${Is_Archive}" != "true" ] && [ "${Is_Archive}" != "false" ]; then
    echo "The input file is in invalid format: The first line contains an invalid Use Archive value."
    exit 1
fi

# Check if the second line is valid
Possible_Archived_Formats=("zip" "rar" "tar")
read -a Allowed_Archived_Formats <<< "${input_file[1]}"
for format in "${Allowed_Archived_Formats[@]}"; do
    if [[ ! " ${Possible_Archived_Formats[@]} " =~ " $format " ]]; then
        echo "The input file is in invalid format: The second line contains an invalid Allowed Archived Format."
        exit 1
    fi
done

# Check if the third line is valid
Possible_Programming_Languages=("c" "cpp" "python" "sh")
read -a Allowed_Programming_Languages <<< "${input_file[2]}"
for language in "${Allowed_Programming_Languages[@]}"; do
    if [[ ! " ${Possible_Programming_Languages[@]} " =~ " $language " ]]; then
        echo "The input file is in invalid format: The third line contains an invalid Allowed Programming Languages."
        exit 1
    fi
done

# Check if the fourth line is valid
Total_Marks="${input_file[3]}"
if [[ ! "${Total_Marks}" =~ ^[0-9]+$ ]]; then
    echo "The input file is in invalid format: The fourth line contains an invalid Total Marks."
    exit 1
fi

# Check if the fifth line is valid
Output_Penalty="${input_file[4]}"
if [[ ! "${Output_Penalty}" =~ ^[0-9]+$ ]]; then
    echo "The input file is in invalid format: The fifth line contains an invalid Penalty for Unmatched/Non-existent Output."
    exit 1
fi

# Check if the sixth line is valid
Working_Directory="${input_file[5]}"
if [ ! -d "$Working_Directory" ]; then
    echo "The input file is in invalid format: The sixth line contains an invalid Working Directory."
    exit 1
fi

# Check if the seventh line is valid
read -a Student_ID_Range <<< "${input_file[6]}"
if [ ${#Student_ID_Range[@]} -ne 2 ]; then
    echo "The input file is in invalid format: The seventh line contains an invalid Student ID Range."
    exit 1
fi
read First_Student_ID Last_Student_ID <<< "${Student_ID_Range[@]}"
if [[ ! "${First_Student_ID}" =~ ^[0-9]+$ ]] || [[ ! "${Last_Student_ID}" =~ ^[0-9]+$ ]]; then
    echo "The input file is in invalid format: The seventh line contains an invalid First or Last Student ID."
    exit 1
fi

# Check if the eighth line is valid
Expected_Output_File="${input_file[7]}"
if [ ! -f "$Expected_Output_File" ]; then
    echo "The input file is in invalid format: The eighth line contains an invalid Expected Output File Location."
    exit 1
fi

# Check if the ninth line is valid
Submission_Penalty="${input_file[8]}"
if [[ ! "${Submission_Penalty}" =~ ^[0-9]+$ ]]; then
    echo "The input file is in invalid format: The ninth line contains an invalid Penalty for Submission Guidelines Violations."
    exit 1
fi

# Check if the tenth line is valid
Plagiarism_Analysis_File="${input_file[9]}"
if [ ! -f "$Plagiarism_Analysis_File" ]; then
    echo "The input file is in invalid format: The tenth line contains an invalid Plagiarism Analysis File."
    exit 1
fi

# Check if the eleventh line is valid
Plagiarism_Penalty="${input_file[10]}"
if [[ ! "${Plagiarism_Penalty}" =~ ^[0-9]+$ ]]; then
    echo "The input file is in invalid format: The eleventh line contains an invalid Plagiarism Penalty."
    exit 1
fi

# Create an array to store the possible extensions
Allowed_Extensions=()
# Loop through each programming language and add the corresponding extension
for language in "${Allowed_Programming_Languages[@]}"; do
    case "$language" in
        "c") Allowed_Extensions+=("c");;
        "cpp") Allowed_Extensions+=("cpp");;
        "python") Allowede_Extensions+=("py");;
        "sh") Allowed_Extensions+=("sh");;
    esac
done

# change the directory to the working directory
if ! cd "$Working_Directory"; then
    echo "Error: Unable to change directory to the working directory."
    exit 1
fi

# Create a csv file to store the marks
Marks_File="marks.csv"
# Write the CSV header
echo "id, marks, marks_deducted, total_marks, remarks" > "$Marks_File"

# Create a directory to store problematic submissions and valid submissions
Problematic_Submissions="issues"
Valid_Submissions="checked"
mkdir -p "$Problematic_Submissions" "$Valid_Submissions"

# Loop through the student directories
for Student_ID in $(seq "$First_Student_ID" "$Last_Student_ID"); do
    skip_evaluation="false"
    marks=0
    marks_deducted=0
    total_marks=0
    remarks=""
    file_name=$(find . -maxdepth 1 -name "${Student_ID}*" -print -quit | sed 's|^\./||')
    if [ -f "$file_name" ]; then
        extension="${file_name##*.}"
        if [[ " ${Possible_Archived_Formats[@]} " =~ " $extension " ]]; then
            if [[ " ${Allowed_Archived_Formats[@]} " =~ " $extension " ]]; then
                if [ "${Is_Archive}" == "false" ]; then
                    marks_deducted=$((marks_deducted + Submission_Penalty))
                    remarks+="Expected unarchived but submitted archived; "
                fi
                mkdir -p extracted
                case "$extension" in
                    "zip") unzip -q "$file_name" -d extracted;;
                    "rar") unrar x "$file_name" extracted &> /dev/null;;
                    "tar") tar -xf "$file_name" -C extracted;;
                esac
                cd extracted
                file_count=$(find . -maxdepth 1 -mindepth 1 | wc -l)
                if [ $file_count -eq 1 ]; then
                    dir_count=$(find . -maxdepth 1 -mindepth 1 -type d | wc -l)
                    if [ $dir_count -eq 1 ]; then
                        dir_name=$(find . -maxdepth 1 -mindepth 1 -type d -exec basename {} \;)
                        if [ "$dir_name" != "$Student_ID" ]; then
                            mv "$dir_name" "$Student_ID"
                            marks_deducted=$((marks_deducted + Submission_Penalty))
                            remarks+="issue case #4; "
                        fi
                        mv "$Student_ID" ..
                        cd ..
                        rm -r extracted
                    else
                        cd ..
                        mv extracted "$Student_ID"
                    fi
                else
                    cd ..
                    mv extracted "$Student_ID"
                fi
            else
                skip_evaluation="true"
                remarks="issue case #2; "
            fi
        elif [[ " ${Possible_Programming_Languages[@]} " =~ " $extension " ]]; then
            if [[ " ${Allowed_Programming_Languages[@]} " =~ " $extension " ]]; then
                if [ "${Is_Archive}" == "true" ]; then
                    marks_deducted=$((marks_deducted + Submission_Penalty))
                    remarks+="Expected archived but submitted unarchived; "
                fi
                mkdir -p "$Student_ID"
                mv "$file_name" "$Student_ID"
            else
                skip_evaluation="true"
                remarks="issue case #3; "
            fi
        else
            skip_evaluation="true"
            remarks+="Invalid file extension"
        fi
    elif [ -d "$file_name" ]; then
        marks_deducted=$((marks_deducted + Submission_Penalty))
        remarks+="issue case #1; "
    else
        skip_evaluation="true"
        remarks+="missing submission"
    fi
    if [ -d "$Student_ID" ]; then
        cd "$Student_ID"
        files_starting_with_Student_ID=$(find . -maxdepth 2 -name "${Student_ID}*" -print | sed 's|^\./||')
        fils_extension=""
        first_matching_file=""
        for file in $files_starting_with_Student_ID; do
            fils_extension="${file##*.}"
            for extension in "${Allowed_Extensions[@]}"; do
                if [ "$fils_extension" == "$extension" ]; then
                    first_matching_file="$file"
                    break 2
                else
                    first_matching_file=""
                fi
            done
        done
        if [ -f "$first_matching_file" ]; then
            generated_output_file="${Student_ID}_output.txt"
            case "$fils_extension" in
                "c") 
                    gcc -o "${Student_ID}" "${Student_ID}.c"
                    "./${Student_ID}" >> "${generated_output_file}"
                    rm "${Student_ID}"
                    ;;
                "cpp")
                    g++ -o "${Student_ID}" "${Student_ID}.cpp"
                    "./${Student_ID}" >> "${generated_output_file}"
                    rm "${Student_ID}"
                    ;;
                "py")
                    python3 "${Student_ID}.py" >> "${generated_output_file}"
                    ;;
                "sh")
                    bash "${Student_ID}.sh" >> "${generated_output_file}"
                    ;;
            esac

            cd ..
            mv -f "$Student_ID" "$Valid_Submissions"
        else
            skip_evaluation="true"
            remarks="issue case #3; "
            cd ..
            mv "$Student_ID" "$Problematic_Submissions"
        fi
    fi
    total_marks=$((marks - marks_deducted))
    echo "${Student_ID}, ${marks}, ${marks_deducted}, ${total_marks}, ${remarks}" >> "$Marks_File"
done