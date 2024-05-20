#!/bin/bash

# Install Mango if its not installed

RED='\033[0;31m'
GREEN='\033[0;32m'
BOLD='\033[1m'
NC='\033[0m' # No Color

if which mango >/dev/null; then
    echo -e "${GREEN}Mango is ${BOLD}already installed${NC}${GREEN}.${NC}"
    exit 0
fi
echo -e "${RED}Mango is ${BOLD}not installed${NC}${RED}.${NC}"

#ask if user wants to install mango
read -p "Do you want to install Mango? [y/n]: " -n 1 -r
echo
if [[ ! $REPLY =~ ^[Yy]$ ]]; then
    echo -e "${RED}Mango installation ${BOLD}cancelled${NC}${RED}.${NC}"
    exit 0
fi
sudo rm /bin/mango
sudo curl https://raw.githubusercontent.com/Clement-Z4RM/Mango/main/mango.py -o /bin/mango && sudo chmod +x /bin/mango
echo -e "${GREEN}Mango is now ${BOLD}installed${NC}${GREEN}.${NC}"
