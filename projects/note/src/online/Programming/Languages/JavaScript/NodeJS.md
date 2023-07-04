# NodeJS

From [Internshala Training NodeJS Course](https://trainings.internshala.com/nodejs-training)

# Require

- Import node module

    ```jsx
    const { readFs } = require("fs");
    const { readHttps } = require("https");
    ```

- Input the string in `console.log`.

    ```jsx
    st readLine = require("readline").createInterface({
      output: process.stdout,
      input: process.stdin,
    });

    readLine.question("What is your name?\n", (name) => {
      console.log(`Welcome ${name}`);
      readLine.close();
    });

    // What is your name?
    // Jimmin <= Ask to input here
    // Welcome Jimmin
    ```


# Module

- Process

    The `process` object in Node.js is a global object that can be accessed inside any module without requiring it.

    - `process.on`

        ```jsx
        process.on('beforeExit', (code) => {
        console.log('Process beforeExit event with code: ', code);
        });
        // Process beforeExit event with code:  0                                                                                             /0.3s
        ```

    - Process expressions

        ```jsx
        console.log(process.ppid);
        // 21321
        console.log(process.argv);
        // [
        //  '/snap/node/5148/bin/node',
        //  '/home/kurama/Documents/Projects/Node JS/app.js'
        //]
        console.log(`Reports are compact? ${process.report.compact}`);
        // Reports are compact? false                                                                                                         /0.3s
        ```

- Module

    The `module` is same as process but you can only access within the file information.

- Event
    - EventEmitter

        ```jsx
        const events = require("events");
        const eEmitter = new events.EventEmitter();

        const getParty = function () {
          console.log("Time to party");
          const ran = Math.ceil(Math.random() * 10);
          console.log(`Party starts in ${ran}`);
          tester(ran);
        };

        eEmitter.on("music", getParty);

        tester(2);

        function tester(val) {
          setTimeout((e) => {
            eEmitter.emit("music");
          }, val * 1000);
        }

        // Time to party
        // Party starts in 5
        // Time to party
        // Party starts in 8
        // Time to party
        // Party starts in 3
        // Time to party
        // Party starts in 9
        ```
