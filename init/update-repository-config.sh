#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BOLD='\033[1m'
NC='\033[0m' # No Color

if [ -f .repository-config.json ]; then
    if grep -q '"repository-init": true' .repository-config.json; then
        echo -e "${GREEN}${BOLD}.repository-config.json${NC}${GREEN} is already updated.${NC}"
    else
        jq '. + {"repository-init": true}' .repository-config.json > tmp.$$.json && mv tmp.$$.json .repository-config.json
        echo -e "${GREEN}${BOLD}.repository-config.json${NC}${GREEN} updated.${NC}"
    fi
else
    echo '{"repository-init": true}' > .repository-config.json
    echo -e "${GREEN}${BOLD}.repository-config.json${NC}${GREEN} created.${NC}"
fi
