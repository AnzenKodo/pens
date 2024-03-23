package main

import (
    "flag"
    "net/http"
    "log"
    "os"
    "os/exec"
    "runtime"
    "fmt"
)

var MOD_NAME string

func main() {
    pwd, err := os.Getwd()
    if err != nil {
        log.Fatal(err)
        os.Exit(1)
    }

	dir := flag.String("d", ".", "Directory to serve")
    port := flag.String("p", "8100", "Port to serve on")
    help := flag.Bool("h", false, "Print help message");
    open := flag.Bool("o", false, "Open default browser");
    flag.Set("h", "help")
    flag.Set("o", "open")
    flag.Parse()

    if *help {
        fmt.Println(MOD_NAME, "is Go File Server\n")
        fmt.Println("Usage of", MOD_NAME+":");
        flag.PrintDefaults()
        fmt.Println("\nSPDX-License-Identifier: MIT (https://spdx.org/licenses/MIT)")
        os.Exit(0)
    }

    url := "http://localhost:"+*port

    if *open {
	    switch runtime.GOOS {
	        case "linux":
	        	err = exec.Command("xdg-open", url).Start()
	        case "windows":
	        	err = exec.Command("rundll32", "url.dll,FileProtocolHandler", url).Start()
	        case "darwin":
	        	err = exec.Command("open", url).Start()
	        default:
	        	log.Fatal("unsupported platform")
	    }
	    if err != nil {
	    	log.Fatal(err)
	    }
    }

	log.Println("Serving", pwd, "on", url)
	log.Fatal(http.ListenAndServe(":"+*port, http.FileServer(http.Dir(*dir))))
}
