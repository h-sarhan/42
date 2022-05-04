
PURPLE="\033[0;35m"
BLUE="\033[0;34m"
RESET="\033[0m"

SETUP_FILES=$(command find /home/hsarhan/42 -name "Makefile_with*" -o -type d -name "c_unit")

cp -r $SETUP_FILES .

echo -e "${PURPLE}Copied setup files:\n${BLUE}${SETUP_FILES}${RESET}"
