package main

import "core:fmt"
import "core:strings"

main :: proc() {
    ascii := " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
    total := len(ascii)

    texts :: "Text Text Text Text"
    pass := "Password"

    count := 0
    for text in texts {
        text_index: int = strings.index_byte(ascii, u8(text))
        count_index: int = strings.index_byte(ascii, u8(pass[count]))

        ciper := (text_index + count_index) % total
        deciper := (ciper - count_index) % total

        fmt.println(text_index, ": ", deciper)
        count += 1
        if len(pass) == count {
            count = 0
        }
    }
}
