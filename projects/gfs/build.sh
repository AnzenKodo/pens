MOD_NAME=$(go list -m)
go build -o $HOME/Apps/bin -ldflags="-X 'main.MOD_NAME=$MOD_NAME'" .
