[#](#) Bash

- Functions Info

    **apropos** - List of man pages for possible matches based on a search term.


## Commands

- Man Page Organization

    [Man Page](Bash%20da610a137ca64195bdf4ec37d6e4274b/Man%20Page%202df02a5a631a4ebe9bcfd37a72009fc0.csv)

- Redirecting Standard Output

    ```bash
    ls -l /usr/bin > ls-output.txt
    ```

    - This makes output of ls command
- About `uniq`
    - `uniq` to remove any duplicates from the output of the `sort` command.

    ```bash
    ls /bin /usr/bin | sort | uniq
    ```

    - To see the list of duplicates instead, add the `d` option to `uniq`

    ```bash
    ls /bin /usr/bin | sort | uniq -d
    ```

- About `tee`
    - `tee` is like `ls > output.txt` but it can work with grep command.

    ```bash
    ls /usr/bin | tee ls.txt | grep zip
    ```

    ## About `echo`

    ```bash
    echo $((2 + 2))
    ```

- Symbols

    [Symbols](Bash%20da610a137ca64195bdf4ec37d6e4274b/Symbols%20d88a1a92cda7446fa8a9d2c975c8947e.csv)

- `echo` Arithmetic Exponentiation can be nested

    ```bash
    echo $(($((5**2)) * 3))
    ```

- The range of integers.

    ```bash
    echo {1..10}
    echo a{A{1,2},B{3,4}}b
    ```

- Enverment Value List

    ```bash
    cli printenv | less
    set | less
    ```


## History

- To see the history

    ```bash
    history
    ```

- History Command

    [History Command](Bash%20da610a137ca64195bdf4ec37d6e4274b/History%20Command%205694bb062b694eb68fa66879592e9106.csv)

- History Expansion Commands

    [History Expansion Commands](Bash%20da610a137ca64195bdf4ec37d6e4274b/History%20Expansion%20Commands%204935186cd0cd4e49a5c894c0463b2851.csv)

- To record the command

    ```bash
    script
    ```


## Permissions

- To see the group number

    ```bash
    id
    ```

- File Type

    [File Type](Bash%20da610a137ca64195bdf4ec37d6e4274b/File%20Type%20b93329415ef14da18905fe8e533748f4.csv)

- Permission Attributes -rwxrwxr–

    [Permission Attributes -rwxrwxr–](Bash%20da610a137ca64195bdf4ec37d6e4274b/Permission%20Attributes%20-rwxrwxr%E2%80%93%2035ff6cb19e8645a3b96ba09a33eba035.csv)

- File Modes in Binary and Octal

    [File Modes in Binary and Octal](Bash%20da610a137ca64195bdf4ec37d6e4274b/File%20Modes%20in%20Binary%20and%20Octal%208ac1bb600cca40ebb1db460155009adb.csv)

- The attribute for changing the file permission
    - `7 (rwx)`, `6 (rw-)`, `5 (r-x)`, `4 (r--)`, and `0 (---)`
- `chmod` Symbolic Notation

    [chmod Symbolic Notation](Bash%20da610a137ca64195bdf4ec37d6e4274b/chmod%20Symbolic%20Notation%2036655aed32be491d8cf121e4b3981626.csv)

    [chmod Symbolic Notation Examples](Bash%20da610a137ca64195bdf4ec37d6e4274b/chmod%20Symbolic%20Notation%20Examples%20d2fdf09328984fce96f5699222acfa25.csv)

- `umask` command controls the default permissions given to a file when it is created.

    ```bash
    umask 005
    ```


## File System

- Testing and Repairing File Systems

    ```bash
    sudo fsck /dev/sdb1
    ```

- Make bootable USB drive

    ```bash
    sudo dd bs=4M if=path/to/input.iso of=/dev/sd<?> conv=fdatasync  status=progress
    ```


## Helpful Command

- Execute `find` file with command use `xargs`

    ```bash
    find ~ -type f -name "index.html" | xargs ls -l
    ```

- Use `find` to find the file

    ```bash
    find ~ -type f -name "index.html"
    ```

- Best way to compress in tar

    ```bash
    tar cfJ playground.tar.xz playground
    ```

- How to Mount ISO File on Linux

    ```bash
    mount -t iso9660 -o loop image.iso /mnt/iso_image
    ```

- How to sort in Linux

    ```bash
    sort -nk 5

    # With command

    ls -l /usr/share | sort -nk 5

    # Sort in ':'

    sort -ht ':' -k 3 /etc/passwd | head
    ```

- Remove Duplicate use `uniq`

    ```bash
    sort foo.txt | uniq
    ```

- Spell check in Terminal

    ```bash
    aspell check filename

    # To check HTML code

    aspell -H check html-filename
    ```

- To make PDF

    ```bash
    ls -l ~/ | pr pr.ps | groff > pr.ps

    # Convert PostScript file into Potable Document File

    ps2pdf pr.ps pr.pdf
    ```

- Good Locations for Scripts
    - `~/bin`Scripts intended for personal use.
    - `/usr/local/bin`Script that everyone on a system is allowed to use.
    - `/usr/local/sbin`Scripts intended for use by the system administrator
    - `/usr/local`Locally supplied software, scripts and compiled programs

# Shell Script

- Assigning Values to Variables and Constants.

    ```bash
    a=z # Assign the string "z" to variable a.
    b="a string" # Embedded spaces must be within quotes.
    c="a string and $b" # Other expansions such as variables can be expanded into the assignment.
    d="$(ls -l foo.txt)" # Results of a command.
    e=$((5 * 7)) # Arithmetic expansion.
    f="\t\ta string\n" # Escape sequences such as tabs and newlines.
    ```

- Using variables with other commands.

    ```bash
    filename="myFile"
    touch file
    mv file ${filename}
    ```

- Here script

    ```bash
    command << token
    text
    token
    ```

- `_EOF_`
    - Example

        ```bash
        # !/bin/bash
        date=$(date +"%x %r %Z")

        cat << _EOF_
        <html>
            <head>
                <title>Website</title>
            </head>
            <body>
                <h1>Website</h1>
                <p>Hello World</p>
            </body>
        </html>
        _EOF_
        ```

    - `_EOF_` with command

        ```bash
        #!/bin/bash
        # Script to retrieve a file via FTP
        FTP_SERVER=ftp.nl.debian.org
        FTP_PATH=/debian/dists/stretch/main/installer-amd64/current/images/
        cdrom REMOTE_FILE=debian-cd_info.tar.gz
        ftp -n << _EOF_
        open $FTP_SERVER
        user anonymous me@linuxbox
        cd $FTP_PATH
        hash
        get $REMOTE_FILE
        bye
        _EOF_
        ls -l "$REMOTE_FILE"
        ```

    - `_EOF_` with `-`

        ```bash
        # !/bin/bash
        date=$(date +"%x %r %Z")

        cat <<- _EOF_
        <html>
            <head>
                <title>Website</title>
            </head>
            <body>
                <h1>Website</h1>
                <p>Hello World</p>
            </body>
        </html>
        _EOF_
        ```

- Shell Functions

    ```bash
    # !/bin/bash

    z=human # Gobal variable

    echo_1() {
    echo "hello"
    return
    }

    echo_2() {
    i=world # local veariable
    echo "world"
    return
    }

    echo ${echo_1} ${echo_2} $z
    ```

- Flow Control: Branching with if
    - `if`

        ```bash
        x=5
        if [ "$x" -eq 5 ]; then
        echo "x equals 5."
        else
        echo "x does not equal 5."
        fi
        ```

    - `if` in shell

        ```bash
        if [ “$x” -eq 5 ]; then echo "equals 5"; else echo "does not equal 5"; fi
        ```

    - `if`, `elif` and `else`

        ```bash
        if commands; then
        commands
        [elif commands; then
        commands...]
        [else
        commands]
        fi
        ```


## Expressions Examples

- File Expressions

    ```bash
    #!/bin/bash
    # test-file: Evaluate the status of a file
    FILE=~/.bashrc
    if [ -e "$FILE" ]; then
    if [ -f "$FILE" ]; then
    echo "$FILE is a regular file."
    fi
    if [ -d "$FILE" ]; then
    echo "$FILE is a directory."
    fi
    if [ -r "$FILE" ]; then
    echo "$FILE is readable."
    fi
    if [ -w "$FILE" ]; then
    echo "$FILE is writable."
    fi
    if [ -x "$FILE" ]; then
    echo "$FILE is executable/searchable."
    fi
    else
    echo "$FILE does not exist"
    exit 1
    fi
    exit
    ```

- String Expressions

    ```bash
    #!/bin/bash
    # test-string: evaluate the value of a string
    ANSWER=maybe
    if [ -z "$ANSWER" ]; then
    echo "There is no answer." >&2
    exit 1
    fi
    if [ "$ANSWER" = "yes" ]; then
    echo "The answer is YES."
    elif [ "$ANSWER" = "no" ]; then
    echo "The answer is NO."
    elif [ "$ANSWER" = "maybe" ]; then
    echo "The answer is MAYBE."
    else
    echo "The answer is UNKNOWN."
    fi
    ```

- Integer Expressions

    ```bash
    #!/bin/bash
    # test-integer: evaluate the value of an integer.
    INT=-5
    if [ -z "$INT" ]; then
    echo "INT is empty." >&2
    exit 1
    fi
    if [ "$INT" -eq 0 ]; then
    echo "INT is zero."
    else
    if [ "$INT" -lt 0 ]; then
    echo "INT is negative."
    else
    echo "INT is positive."
    fi
    if [ $((INT % 2)) -eq 0 ]; then
    echo "INT is even."
    else
    echo "INT is odd."
    fi
    fi
    ```

- File Expressions

    | Expression | Is True If: |
    | --- | --- |
    | file1 -ef file2 | file1 and file2 have the same inode numbers (the two filenames refer to the same file by hard linking). |
    | file1 -nt file2 | file1 is newer than file2. |
    | file1 -ot file2 | file1 is older than file2. |
    | -b file | file exists and is a block-special (device) file. |
    | -c file | file exists and is a character-special (device) file. |
    | -d file | file exists and is a directory. |
    | -e file | file exists. |
    | -f file | file exists and is a regular file. |
    | -g file | file exists and is set-group-ID. |
    | -G file | file exists and is owned by the effective group ID. |
    | -k file | file exists and has its “sticky bit” set. |
    | -L file | file exists and is a symbolic link. |
    | -O file | file exists and is owned by the effective user ID. |
    | -p file | file exists and is a named pipe. |
    | -r file | file exists and is readable (has readable permission for the effective user). |
    | -s file | file exists and has a length greater than zero. |
    | -S file | file exists and is a network socket. |
    | -t fd | fd is a file descriptor directed to/from the terminal. This can be used to determine whether standard input/output/error is being redirected. |
    | -u file | file exists and is setuid. |
    | -w file | file exists and is writable (has write permission for the effective user). |
    | -x file | file exists and is executable (has execute/search permission for the effective user). |

- String Expressions

    | Expression | Is True If… |
    | --- | --- |
    | string | string is not null. |
    | -n string | The length of string is greater than zero. |
    | -z string | The length of string is zero. |
    | `string1 = string2` `string1 == string2` | string1 and string2 are equal. Single or double equal signs may be used. The use of double equal signs is supported by bash and is generally preferred, but it is not POSIX compliant. |
    | string1 != string2 | string1 and string2 are not equal. |
    | string1 > string2 | string1 sorts after string2. |
    | string1 < string2 | string1 sorts before string2. |

- Integer Expressions

    | Expression | Is True If… |
    | --- | --- |
    | integer1 -eq integer2 | integer1 is equal to integer2. |
    | integer1 -ne integer2 | integer1 is not equal to integer2. |
    | integer1 -le integer2 | integer1 is less than or equal to integer2. |
    | integer1 is less than or equal to integer2. | integer1 is less than integer2. |
    | integer1 -ge integer2 | integer1 is greater than or equal to integer2. |
    | integer1 -gt integer2 | integer1 is greater than integer2. |
