package cipher

import "core:fmt"
import "core:os"
import "core:encoding/base32"

algo :: proc(meth: string, mess: string, pass: string) {
    count := 0
    encode :[dynamic]u8

    mess64 := mess
    if meth == "-d" {
        decode :[dynamic]u8
        for i in base32.decode(mess) {
            append(&decode, i)
        }
        #reverse for i in decode {
            if (i != 0) { break }
            pop(&decode)
        }
        mess64 = string(decode[0: len(decode)])
    }

    for _, index in mess64 {
        mess_index := int(mess64[index])
        pass_index := int(pass[count])

        if meth == "-e" {
            append(&encode, u8(mess_index + pass_index))
        }
        if meth == "-d" {
            fmt.printf("%c", mess_index - pass_index)
        }

        count += 1
        if len(pass) == count {
            count = 0
        }
    }

    if meth == "-e" {
        fmt.println(base32.encode(encode[:]))
    }
}

main :: proc() {
    if len(os.args) == 1 || os.args[1] == "-h" {
        fmt.println(`cipher is cli application that encript and decript text with Caesar Cipher encription method.
Usage:
    cipher -p [password] -[method] [data]
Commands:
    -p      Encription password

    -e      To encript data
    -d      To decript data

    -h      For help message
`)
        return
    }

    pass := ""
    mess := ""
    meth := ""
    for arg, i in os.args {
        if arg == "-p" {
            pass = os.args[i + 1]
        }
        if arg == "-e" || arg == "-d"{
            meth = os.args[i]
            mess = os.args[i + 1]
        }
    }

    if pass == "" {
        fmt.println("Error: parameter -p with password not found.\n")
        return
    }
    if meth == "" {
        fmt.println("Error: method [-e or -d] is not provided.\n")
        return
    }
    if mess == "" {
        fmt.println("Error: message after [-e or -d] method is not provided.\n")
        return
    }

    algo(meth, mess, pass)
}
