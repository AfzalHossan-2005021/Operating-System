# Define variables for the zip file, output directory, and script
ZIP_FILE := test-cases.zip
OUTPUT_DIR := test-cases
SCRIPT := 2005021.sh

# Target to unzip the file
unzip: $(ZIP_FILE)
	@echo "Unzipping $(ZIP_FILE)..."
	@unzip -o $(ZIP_FILE)
	@echo "Unzipped $(ZIP_FILE)"

# Target to run the script after unzipping
run-script: unzip $(SCRIPT)
	@echo "Running the shell script..."
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/1/input/sample_input.txt
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/2/input/sample_input.txt
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/3/input/sample_input.txt
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/4/input/sample_input.txt
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/5/input/sample_input.txt
	@bash $(SCRIPT) -i $(OUTPUT_DIR)/6/input/sample_input.txt

# Clean target to remove the output directory and any extracted files
clean:
	@echo "Cleaning up..."
	@rm -rf $(OUTPUT_DIR)
	@echo "Cleaned $(OUTPUT_DIR)"