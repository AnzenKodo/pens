@echo off

set BUILD_DIR=build

echo Compiling the program...
javac -Xlint:unchecked Main.java GUI.java DB.java -d %BUILD_DIR%
if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed! Check errors above.
    exit /b
)

echo Running the program...
java -classpath %BUILD_DIR%;jars\mssql-jdbc-12.10.1.jre11.jar Main
if %ERRORLEVEL% NEQ 0 (
    echo Some error occur while running Program.
    exit /b
)
