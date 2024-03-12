package main

import (
	"log"
	"net/http"
	"os"
	"fmt"
	"io"
)

func main() {
    var dirname string
    if len(os.Args) < 2 {
        dirname = "."
    } else {
        dirname = os.Args[1]
    }
    fmt.Println(dirname)

    fs := http.FileServer(http.Dir(dirname))
    var handler http.HandlerFunc
    handler = func(w http.ResponseWriter, r *http.Request) {
        var (
            url   = r.URL.Path
            isDir = url[len(url)-1] == '/'
        )
        fs.ServeHTTP(w, r)
        if isDir {
            io.WriteString(w, "hello")
        }
    }

	log.Fatal(http.ListenAndServe(":8080", handler))
}
