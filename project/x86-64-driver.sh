#! /bin/bash

data_segment() {
    {
        cat <<EOF
.data
    format:     .ascii  "%d\n"
.bss
EOF
        ALPHA="a b c d e f g h i j k l m n o p q r s t u v w x y z"
        for a in $ALPHA; do
            echo -e "$a:\t.quad\t0"
        done

        cat <<EOF
.text
    .globl main
main:
EOF
    } >> "$1"
}

exit_segment() {
    {
        cat <<EOF
    movq    \$1,%rdi
    call    exit
EOF
    } >> "$1"
}

basic_compiler() {
    # Ensure input file path is provided
    if [ "$#" -ne 1 ]; then
        echo " ERROR: Please provide the input file path."
        exit 1
    fi

    input_file_path="$1"

    if [[ ! -f "$input_file_path" ]]; then
        echo " ERROR: $input_file_path does not exist in the provided path."
        exit 1
    fi

    filename_with_extension=$(basename "$input_file_path")
    if [ "${filename_with_extension: -5}" != ".calc" ]; then
        echo " ERROR: Please provide a filename with .calc as the suffix."
        exit 1
    fi

    # Rest of the compiler logic
    local filename="${filename_with_extension%.calc}"
    local filename_with_s="$filename.s"

    echo "" > "./build/$filename_with_s"
    data_segment "./build/$filename_with_s"

    ./bin/calc3i < "$input_file_path" >> "./build/$filename_with_s"

    exit_segment "./build/$filename_with_s"
    gcc -c "./build/$filename_with_s" -o "./object/$filename.a"
    gcc -no-pie ./lib/* "./object/$filename.a" -o "./bin/$filename"
    
    # Input validation
    echo ""
    echo "Compiler for assembler code, accepts a file with '.calc' as extension to produce an assembler code and its executable program!"
    echo ""
    echo ""
}

# Get the input file path as an argument
input_file_path="$1"

# Call the basic_compiler function with the input file path
basic_compiler "$input_file_path"
exit 0