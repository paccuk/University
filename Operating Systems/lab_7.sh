#!bin/bash

l_param() {
    modules=($(find /sys/module/ -name "refcnt" -exec dirname {} + | sort))
    result="$(printf "%-25s %-15s %-15s" "Module" "Users count" "Used by")\n\n"

    for ((i = 0; i < ${#modules[@]}; i++)); do
        name="$(cut -d'/' -f4 <<<${modules[i]})"
        users_count="$(cat "${modules[i]}/refcnt")"
        used_by="$(ls -m "${modules[i]}/holders" | tr '\n' ' ')"

        result+="$(printf '%-25s %-15s %s' "$name" "$users_count" "$used_by")\n"
    done
    printf "$result"
}

b_param() {
    modules=($(find /sys/module/ -maxdepth 1 -not -path "*/refcnt" | sort))
    result="$(printf "%-25s %s" "Module" "Parameters")\n"

    for ((i = 0; i < ${#modules[@]}; i++)); do
        name="$(cut -d'/' -f4 <<<${modules[i]})"
        params="$(ls -m "${modules[i]}/parameters" 2>/dev/null | tr '\n' ' ')"

        result+="$(printf '%-25s %-15s %s' "$name" "$params")\n"
    done
    printf "$result"
}

while getopts lb option; do
    case $option in
    l)
        l_param
        exit
        ;;
    b)
        b_param
        exit
        ;;
    \?)
        echo "Error: Invalid option"
        exit
        ;;
    esac
done
