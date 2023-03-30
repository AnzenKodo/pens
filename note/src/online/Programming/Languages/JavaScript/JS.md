# The JavaScript language

# Standard built-in objects

## Proxy

- The `new Proxy` object enables you to create a proxy for another object, which can intercept and redefine fundamental operations for that object.

    ```jsx
    let numbers = {
        'Hello': 'Hi',
        'YoYo': 'Yo',
        'Going': 'Go'
    }

    let proxy = new Proxy(numbers, {
        get(target, prop) {
            if(prop in target) {
                return target[prop];
            } else {
                return `${prop} is not found`;
            }
        }
    });

    proxy['Going'];
    // Go
    ```

- Proxy with `set` **Note**: For set, it must return true for a successful write.

    ```jsx
    let users = {};

    let dataStorage = new Proxy(users, {
        set(target, prop, val) {
            if(typeof val == 'string') {
                target[prop] = val;
            } else {
                throw new Error(`Only string allowed`);
            }
        }
    });

    dataStorage.name = "Jone"
    // Jone

    dataStorage.age = 12
    // Error: Only string allowed
    ```

- Proxy with `has`

    ```jsx
    let range = {
        start: 1,
        end: 10
    };

    let range = new Proxy(range, {
        has(target, prop) {
            return target.start < prop && target.end > prop;
        }
    });

    alert(5 in range); // true
    alert(50 in range); // false
    ```


## Reflect

- `Reflect.ownKeys()` returns an array of the target object's own property keys.

    ```jsx
    let user = {
      name: "John",
      age: 30,
      _password: "***"
    };

    let user = new Proxy(user, {
        ownKey(target) {
            return Object.keys(target).filter(obj => !obj.startsWith('_'));
        }
    });

    for(let key in user) alert(key);
    // name, age
    ```

- `Reflect.set()`

    ```jsx
    user = {
    	age: 32
    }
    Reflect.set(user, 'name', 'Jone');
    Reflect.set(user, 'age', '53');

    console.log(user);

    {age: "53", name: "Jone"}
    ```

- Proxying a getter with `Reflect.get()`.

    ```jsx
    let user = {
        _name: "Guest",
        get name() {
            return this._name;
        }
    }

    let userProxy = new Proxy(user, {
        get(target, prop, receiver) {
            return Reflect.get(target, prop, receiver);
        }
    });

    let admin = {
        __proto__: userProxy,
        _name: "Admin"
    };

    admin.name;
    // Admin
    ```


## Promise

- Return value if fail or pass.

    ```jsx
    let passPromise = new Promise((reslove, reject) => {
    	try {
    		if (false) throw NotDefine();
    		reslove("Pass");
    	} catch(err) {
    		reject(err.message);
    	}
    });

    passPromise.then(result => console.log(result), failResult => console.log(failResult))
    // Pass

    let failPromise = new Promise((reslove, reject) => {
    	try {
    		if (true) throw NotDefine();
    		reslove("Pass");
    	} catch(err) {
    		reject(err.message);
    	}
    });

    failPromise.then(result => console.log(result), failResult => console.log(failResult))
    // NotDefine is not defined
    ```

- Promise with `finally`.

    ```jsx
    let failPromise = new Promise((reslove, reject) => {
    	try {
    		if (true) throw NotDefine();
    		reslove("Pass");
    	} catch(err) {
    		reject("Fail: " + err.message);
    	}
    })
    	.finally(() => console.log("The result is:"));

    failPromise.then(result => console.log(result), failResult => console.log(failResult))
    // The result is
    // NotDefine is not defined
    ```

- Promise with `catch`.

    ```jsx
    let failPromise = new Promise((reslove, reject) => {
    	try {
    		if (true) throw NotDefine();
    		reslove("Pass");
    	} catch(err) {
    		reject("Fail: " + err.message);
    	}
    })
    	.finally(() => console.log("The result is:")
    	.catch((err) => console.log(err.name + ": This error is catch."));

    failPromise.then(result => console.log(result), failResult => console.log(failResult))
    // The result is
    // undefined: This error is catch.
    ```

- ❓Delay with a promise.

    ```jsx
    function delay(ms) {
        return new Promise((reslove) => setTimeout(reslove, ms));
    }

    delay(3000).then(() => alert('runs after 3 seconds'));
    // runs after 3 seconds
    ```

- Promises chaining with `then`

    ```jsx
    new Promise((reslove, reject) => {
        reslove("Hello");
    }).then((result) => {
        console.log(result);
        return "how";
    }).then((result) => {
        console.log(result);
        return "are";
    }).then((result) => {
        console.log(result);
    }).finally(() => {
        console.log("you?");
    });
    ```

- Promises chaining with numbers

    ```jsx
    new Promise((reslove) => {
        reslove(1);
    }).then((result) => {
        console.log(result);
        return result + 1;
    }).then((result) => {
        console.log(result);
        return result + 1;
    }).then((result) => {
        console.log(result);
    });

    /*
    1
    2
    3
    */
    ```

- `Promise.all`you can use multiple Promise

    ```jsx
    let username = []

    for ( loop = 0; loop < 2; loop++ ) username.push(prompt("What is your Username"));

    let githubAPI = username.map(user => "https://api.github.com/users/" + user);

    Promise.all(githubAPI)
    	.then(apiJSON => Promise.all(apiJSON.map(aj => aj.json())))
    	.then(check => {
    	if (check == null) {
    		console.log(`No result found`)
    		exit();
    		}
    	return check;
    })
    	.then(github => console.log(`Name: ${github.name}, Repo: ${github.public_repos}`));
    ```

- #`Promise.allSettled`the `Promise.all`can't error this function can.
    - `Promise.allSettled` just waits for all promises to settle, regardless of the result. The resulting array has:
        - `{status:"fulfilled", value:result}` for successful responses,
        - `{status:"rejected", reason:error}` for errors.

    ```jsx
    let urls = [
    	`https://api.github.com/users/aav`,
    	`https://api.github.com/users/hello`,
    	`https://no-such-url`
    ];

    Promise.allSettled(urls.map(url => fetch(url)))
    	.then(url => url.forEach((urlLoop, num) => {
    		if ( urlLoop.status == "fulfilled" ) {
    			fetch(urls[num])
                    .then(urlJSON => urlJSON.json())
                    .then(data => console.log(`${data.name}`));
    		}
    		if ( urlLoop.status == "rejected" ) {
    			console.log(`Error: Failed to fetch. Error code: 3234`);
    		}
    	}));
    ```

- `Promise.race`
    - `reject` or `error` can't come first.

        ```jsx
        Promise.race([
          new Promise((resolve, reject) => reject(1)),
          new Promise((resolve, reject) => resolve(2)),
          new Promise((resolve, reject) => reject(3)),
          new Promise((resolve, reject) => resolve(4))
        ]).then(alert);

        // Uncaught (in promise) 1
        ```

    - Only shows the promise which executes first.

        ```jsx
        Promise.race([
          new Promise((resolve, reject) => setTimeout(() => resolve(2), 200)),
          new Promise((resolve, reject) => setTimeout(() => resolve(4), 100))
        ]).then(alert);
        ```

- `Promise.any`

    ```jsx
    Promise.any([
        new Promise((reslove, reject) => reject(1)),
        new Promise((reslove, reject) => setTimeout(() => reslove(2), 200)),
        new Promise((reslove, reject) => reject(3)),
        new Promise((reslove, reject) => setTimeout(() => reslove(4), 100))
    ]).then(word => console.log(word));
    ```


## Date

- To Get the `Date`
    - `getFullYear()` Get the year (4 digits).
    - `getMonth()` Get the month, from 0 to 11.
    - `getDate()` Get the day of month, from 1 to 31, the name of the method does look a little bit strange.
    - `getHours()`, `getMinutes()`, `getSeconds()`, `getMilliseconds()` Get the corresponding time components.
    - `getDay()` Get the day of week, from 0 (Sunday) to 6 (Saturday). The first day is always Sunday, in some countries that’s not so, but can’t be changed.
    - `getTime()` Returns the timestamp for the date – a number of milliseconds passed from the January 1st of 1970 UTC+0.
    - `getTimezoneOffset()` Returns the difference between UTC and the local time zone, in minutes.
- To Set the `Date`
    - `setFullYear(year, [month], [date])`
    - `setMonth(month, [date])`
    - `setDate(date)`
    - `setHours(hour, [min], [sec], [ms])`
    - `setMinutes(min, [sec], [ms])`
    - `setSeconds(sec, [ms])`
    - `setMilliseconds(ms)`
    - `setTime(milliseconds)`
- #`Date()` constructor.

    ```jsx
    const date1 = new Date('December 17, 1995 03:24:00');
    console.log(date1);
    // Sun Dec 17 1995 03:24:00 GMT+0530 (India Standard Time)
    ```

- #`Date.now()` for now date.

    ```jsx
    let start = Date.now();
    for (let i = 0; i < 100000; i++) {
      let doSomething = i * i * i;
    }
    let end = Date.now();
    console.log( `The loop took ${end - start} ms` );
    // The loop took 2 ms
    ```

- `Date.parse` from a string.

    ```jsx
    let ms = Date.parse('2012-01-26T13:51:50.417-07:00');
    alert(ms);
    // 1327611110417
    ```


## Function

- IIFE (Immediately Invoked Function Expression)

    ```jsx
    ((name, surname) => {
    	console.log(`Hello ${name} ${surname}`);
    })('Jummy', 'Vinchoco');

    // Hello Jummy Vinchoco
    ```

- ❓ Fix a function that loses "this"

    ```jsx
    function askPassword(ok, fail) {
      let password = prompt("Password?", '');
      if (password == "rockstar") ok();
      else fail();
    }

    let user = {
      name: 'John',

      loginOk() {
        alert(`${this.name} logged in`);
      },

      loginFail() {
        alert(`${this.name} failed to log in`);
      },

    };

    askPassword(user.loginOk.bind(user), user.loginFail.bind(user));
    ```

- Arrow don't have `this`, `argument`, `new` & `super`
- #`Function.name`to show variable name

    ```jsx
    function sayHi() {
      alert("Hi");
    }

    alert(sayHi.name); // sayHi
    ```

- #`setter`& #`getter`. #`set` you can change the value like `let`& `const`. #`get`syntax binds an object property to a function that will be called when that property is looked up.
    - This can also work with `defineProperty` & `defineProperties`

        ```jsx
        let user = {
          name: "John",
          surname: "Smith"
        };

        Object.defineProperty(user, 'fullName', {
          get() {
            return `${this.name} ${this.surname}`;
          },

          set(value) {
            [this.name, this.surname] = value.split(" ");
          }
        });

        console.log(user.fullName); // John Smith

        for(let key in user) console.log(user); // name, surname
        ```

    - `getters`/`setters` can be used as wrappers over “real” property values to gain more control over operations with them.

        ```jsx
        let user = {
          get name() {
            return this._name;
          },

          set name(value) {
            if (value.length < 4) {
              alert("Name is too short, need at least 4 characters");
              return;
            }
            this._name = value;
          }
        };

        user.name = "Pete";
        alert(user.name); // Pete

        user.name = ""; // Name is too short...
        ```

- Binding object with function with #`bind`.
    - Joined other function `this` with bind.

        ```jsx
        let user = {
            firstName: "John"
        };

        function func(word) {
            console.log(word + ' ' + this.firstName);
        };

        say("Hi");
        // Hi John
        ```

    - You can solve `this` problem with #`bind`.

        ```jsx
        let user = {
            firstName: "Jonn",
            sayHi() {
                console.log(`Hi ${this.firstName}`);
            }
        }

        user.bind(user.sayHi);
        // Hi Jonn
        ```

- Sort with #`sort()`.

    ```jsx
    let arr = [ 1, 15, 2 ];
    console.log(arr.sort((a, b) => a - b);
    // [1, 2, 15]
    ```

- Sort string #`localeCompare()`.

    ```jsx
    let countries = ['Österreich', 'Andorra', 'Vietnam'];
    console.log(countries.sort((a, b) => a.localeCompare(b)))
    // Andorra, Österreich, Vietnam
    ```

- Reverse the array with #`reverse()`

    ```jsx
    let arr = [1, 2, 3, 4, 5];
    arr.reverse();
    alert( arr );
    // 5,4,3,2,1
    ```

- Checks is it Array or Not with #`isArray()`.

    ```jsx
    console.log(Array.isArray({}));
    // false
    console.log(Array.isArray([]));
    // true
    ```

- Make array with words with `Array.from()`.

    ```jsx
    console.log(Array.from("HELLO"));
    // ["H", "E", "L", "L", "O"]
    ```

- You can function as a variable in function.

    ```jsx
    function f() {
      let value = Math.random();

      return function() { alert(value); };
    }

    // 3 functions in array, every one of them links to Lexical Environment
    // from the corresponding f() run
    let arr = [f(), f(), f()];
    ```

- Both nested functions are created within the same outer Lexical Environment, so they share access to the same count variable.

    ```jsx
    function Counter() {
      let count = 0;

      this.up = function() {
        return ++count;
      };

      this.down = function() {
        return --count;
      };
    }

    let counter = new Counter();

    alert( counter.up() ); // 1
    alert( counter.up() ); // 2
    alert( counter.down() ); // 1
    ```

- The function that created inside the function is stay inside the function.

    ```jsx
    let phrase = "Hello";

    if (true) {
      let user = "John";

      function sayHi() {
        alert(`${phrase}, ${user}`);
      }
    }

    sayHi(); // error
    ```

- Length of String with `length()`.
- Named Function Expression, or NFE, is a term for Function Expressions that have a name.
    - It allows the function to reference itself internally.
    - It is not visible outside of the function.

    ```jsx
    let sayHi = function func(who) {
      if (who) {
        alert(`Hello, ${who}`);
      } else {
        **func("Guest");**
      }
    };

    let welcome = sayHi;
    sayHi = null;

    welcome(); // Hello, Guest
    ```

    - `func` is function-local. It is not taken from outside (and not visible there). The specification guarantees that it will always reference the current function.
- Sum with an arbitrary amount of brackets.

    ```jsx
    function sum(a) {

      let currentSum = a;

      function f(b) {
        currentSum += b;
        return f;
      }

      f.toString = function() {
        return currentSum;
      };

      return f;
    }

    alert( sum(1)(2) ); // 3
    alert( sum(5)(-1)(2) ); // 6
    alert( sum(6)(-1)(-2)(-3) ); // 0
    alert( sum(0)(1)(2)(3)(4)(5) ); // 15
    ```

- The call() method calls a function with a given this value and arguments provided individually.

    ```jsx
    function sayHi() {
        return this.name;
    }

    let hi = { name: "hello boys" };

    sayHi.call( hi ); // hello boys
    ```

- call() method with argument.

    ```jsx
    function sayHi( user ) {
        console.log( this.name + " " + user );
    }

    let id = { name: "Jonney" };
    let username = "Deep";

    sayHi.call( id, username );
    ```

- Function binding
    - The function inside the function run the first the outer function.

        ```jsx
        function handleException(funcAsParameter) {
        	console.log("Inside handleException function")
        	try {
        		funcAsParameter()
        	} catch(err) {
        		console.log(err)
        	}
        }

        function divideByZero() {
        	result = 5 / 0
        	if(!Number.isFinite(result)) {
        		throw "Division by Zero not a good idea!!"
        	}
        	console.log("Result of the division of 5 by zero is: " + result)
        }

        // Passing divide by zero as a parameter to handle exceptions. handleException will
        // call the divide by zero methods and will handle any exception raised by it.
        handleException(divideByZero)
        ```

- IIFE - Self Executing Anonymous Function

    ```jsx
    (function helloWorld(name, age) {
    	console.log(`My name is ${name} and I am ${age} years old`);
    })("Jonney", 32);
    ```


## Array

- `Array`method, selects and negatives.
    - `slice(start, end)` From `start` to `end` (not including `end`) - **Allows negatives**
    - `substring(start, end)` Between `start` and `end` - **Negative values mean** `0`
    - `substr(start, length)`from `start` get `length` characters - **Allows negative** `start`
- #`map()`changes the value of the first variable in arrow function next value in the array

    ```jsx
    const array1 = [1, 4, 9, 16];

    // pass a function to map
    const map1 = array1.map(x => x * 2);

    console.log(map1);
    // expected output: Array [2, 8, 18, 32]
    ```

- #`isArray` checks if it is array or not

    ```jsx
    Array.isArray([1, 2, 3]);  // true
    Array.isArray({foo: 123}); // false
    ```

- #`indexOf`checks if the array has same value and gives `true` = 1 & `false` = 0

    ```jsx
    const beasts = ['ant', 'bison', 'camel', 'duck', 'bison'];

    console.log(beasts.indexOf('bison'));
    // expected output: 1

    // start from index 2
    console.log(beasts.indexOf('bison', 2));
    // expected output: 4

    console.log(beasts.indexOf('giraffe'));
    // expected output: -1
    ```

- `includes` works like `indexOf`but returns `true`& `false`

    ```jsx
    const array1 = [1, 2, 3];

    console.log(array1.includes(2));
    // expected output: true

    const pets = ['cat', 'dog', 'bat'];

    console.log(pets.includes('cat'));
    // expected output: true

    console.log(pets.includes('at'));
    // expected output: false
    ```

- #`forEach`loops through all array values

    ```jsx
    let code = ["hello", "world", "noob"];

    code.forEach(n => console.log(n));
    /*
     hello
     world
     noob
    */
    ```

- `Array` prototypically inherits from `Object`. `console.log(Array instanceof Object) // true`
- The `join()` method creates and returns a new string by concatenating all of the elements in an array.

    ```jsx
    const elements = ['Fire', 'Air', 'Water'];

    console.log(elements.join());
    // expected output: "Fire,Air,Water"

    console.log(elements.join(''));
    // expected output: "FireAirWater"

    console.log(elements.join('-'));
    // expected output: "Fire-Air-Water"
    ```


## JSON

- #`JSON.stringify()` converts a JavaScript object or value to a JSON string.

    ```jsx
    console.log(JSON.stringify({ x: [10, undefined, function(){}, Symbol('')] }));
    ```

- String to Object with `JSON.parse()`

    ```jsx
    let userData = '{ "name": "John", "age": 35, "isAdmin": false, "friends": [0,"hi",2,3] }';
    let user = JSON.parse(userData);
    alert( user.friends[1] );
    // "hi"
    ```

- Only show passed value with `toJSON()`

    ```jsx
    let room = {
      number: 23,
      toJSON() {
        return this.number;
      }
    };
    let meetup = {
      title: "Conference",
      room
    };
    alert( JSON.stringify(room) ); // 23
    alert( JSON.stringify(meetup) );
    /*
      {
        "title":"Conference",
        "room": 23
      }
    */
    ```

- Object to String `JSON.stringify()`

    ```jsx
    let user = {
      name: "John",
      age: 25,
      roles: {
        isAdmin: false,
        isEditor: true
      }
    };
    alert(JSON.stringify(user, null, 2));
    /* two-space indents:
    {
      "name": "John",
      "age": 25,
      "roles": {
        "isAdmin": false,
        "isEditor": true
      }
    }
    */
    /* for JSON.stringify(user, null, 4) the result would be more indented:
    {
        "name": "John",
        "age": 25,
        "roles": {
            "isAdmin": false,
            "isEditor": true
        }
    }
    */
    ```

- JSON in Javascript

    ```jsx
    let string = JSON.stringify({squirrel: false,
                                 events: ["weekend"]});
    console.log(string);
    // → {"squirrel":false,"events":["weekend"]}
    console.log(JSON.parse(string).events);
    // → ["weekend"]
    ```


## Object

- `Object` properties can store beside a value, have three special attributes (so-called “flags”).
    - `writable`- if `true`, the value can be changed, otherwise it’s read-only.
    - `enumerable`- if `true`, then listed in loops, otherwise not listed.
    - `configurable`- if `true`, the property can be deleted and these attributes can be modified, otherwise not.
- With #`getOwnPropertyDescriptor` you can also show object flags.

    ```jsx
    let user = {
        name: "John"
    }

    console.log(Object.getOwnPropertyDescriptor(user, "name"));
    /*
    {
      "value": "John",
      "writable": true,
      "enumerable": true,
      "configurable": true
    }
    */

    console.log(Object.getOwnPropertyDescriptor(user, "name").writable);
    // true
    ```

- To change the flags, we can use #`Object.defineProperty`.
    - `writable: false` value can't be change.

        ```jsx
        let user = {
            name: "John"
        }

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "John",
          "writable": true,
          "enumerable": true,
          "configurable": true
        }
        */

        Object.defineProperty(user, "name", {
            writable: false,
            value: "Jonney"
        });

        user.name = "John"; // Value will not change

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "Jonney",
          "writable": false,
          "enumerable": true,
          "configurable": true
        }
        */
        ```

    - `configurable: false` can't be deleted.
        - The idea of “configurable: false” is to prevent changes of property flags and its deletion, while allowing to change its value.
            - Can’t change `configurable` flag.
            - Can’t change `enumerable` flag.
            - Can’t change `writable: false` to `true` (the other way round works).
            - Can’t change `get/set` for an accessor property (but can assign them if absent).

        ```jsx
        let user = {
            name: "John"
        }

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "John",
          "writable": true,
          "enumerable": true,
          "configurable": true
        }
        */

        Object.defineProperty(user, "name", {
            configurable: false,
            value: "Jonney"
        });

        delete user.name; // Value can't be deleted

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "Jonney",
          "writable": true,
          "enumerable": true,
          "configurable": false
        }
        */
        ```

    - `enumerable: false` can't use `for...in`loop & `Object.key`

        ```jsx
        let user = {
            name: "John",
        		age: 23
        }

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "John",
          "writable": true,
          "enumerable": true,
          "configurable": true
        }
        */

        Object.defineProperty(user, "name", {
            enumerable: false,
            value: "Jonney"
        });

        for (let key in user) console.log(key);
        // age --> don't show name

        console.log(Object.getOwnPropertyDescriptor(user, "name"));
        /*
        {
          "value": "Jonney",
          "writable": true,
          "enumerable": false,
          "configurable": true
        }
        */
        ```

- Unlike #`Object.defineProperty`the #`Object.defineProperties`can change multiple flags.

    ```jsx
    let user = { }

    Object.defineProperties(user, {
    	name: {value: "John", writable: true},
    	age: {value: 30, enumerable: true}
    });

    console.log(Object.getOwnPropertyDescriptor(user, "name"));
    /*
    {
      "value": "Jonney",
      "writable": true,
      "enumerable": false,
      "configurable": false
    }
    */
    ```

- The #`Object.preventExtensions()` method prevents new properties from ever being added to an object.
    - The #`Object.isExtensible()` method determines if an object is extensible.

        ```jsx
        const object1 = {};

        Object.preventExtensions(object1);

        console.log(Object.isExtensible(object1));
        // expected output: false

        Object.defineProperty(object1, 'property1', {
            value: 42
        });

        Object.getOwnPropertyDescriptor(object1);
        // Error
        ```

- The #`Object.freeze()` forbids adding/removing/changing of properties. Sets configurable: false, writable: false for all existing properties.
    - The #`Object.isFrozen()` determines if an object is frozen.

        ```jsx
        const obj = {
          prop: 42
        };

        Object.freeze(obj);

        console.log(Object.isFrozen(obj));
        // true

        obj.prop = 33;
        // Throws an error in strict mode

        console.log(obj.prop);
        // expected output: 42
        ```

- The #`Object.seal()` method seals an object, preventing new properties from being added to it and marking all existing properties as `configurable: false`. You can't delete the value.
    - The #`Object.isSealed()` method determines if an object is sealed.

        ```jsx
        const object1 = {
          property1: 42
        };

        Object.seal(object1);

        console.log(Object.isSealed(object1));

        object1.property1 = 33;
        console.log(object1.property1);
        // expected output: 33

        delete object1.property1; // cannot delete when sealed
        console.log(object1.property1);
        // expected output: 33
        ```

- #`Object.prototype.constructor`
    - #`constructor`shows the variable property match.

        ```jsx
        let o = {};
        console.log(o.constructor === Object);
        // true

        let a = [];
        console.log(a.constructor === Array);
        // true

        let n = new Number;
        console.log(n.constructor === Number);
        // true

        let s = new String;
        console.log(s.constructor === String);
        // true
        ```

    - Create 2nd object using function to object.

        ```jsx
        function Rabbit(name) {
            this.name = name;
        }

        let rabbit = new Rabbit("Mik Bunney");

        console.log(rabbit.name);

        let newRabbit = new rabbit.constructor("Mik Bunney");

        newRabbit.name
        ```

- #`F.prototype`and #`prototype`
    - Use `F.prototype`to connect `Object`to `function` adds value top of `function` value.

        ```jsx
        function username(name, surname) {
            this.name = name;
            this.surname = surname;
        }

        let age = {
        	dob: "18-09-2020"
        }

        username.prototype = age;

        let person = new username("Joney", "Deepth");

        console.log(`Name: ${person.name} ${person.surname}, DOB: ${person.dob}`);
        ```

    - Add `this`value to function without adding value in brackets(`{}`).

        ```jsx
        function Rabbit() {};

        Rabbit.prototype.age = 20;

        let rabbit = new Rabbit();

        console.log(rabbit.age);
        // 20
        ```

    - Make `.function`with prototype.

        ```jsx
        function f() {
        	console.log("Hello");
        }

        Function.prototype.disc = function(number) {
        	console.log(setTimeout(this, number));
        }

        console.log(f.disc(1000));
        ```

    - Make multi-layer brackets.

        ```jsx
        function f(word) {
        console.log(word);
        }

        Function.prototype.disc = function(number) {
        let f = this;
        return function(word) {
        console.log(setTimeout(() => f(word), number));
        }
        }
        ```

- The #`Object.create()` method creates a new object, using an existing object as the prototype of the newly created object.

    ```jsx
    let person = {
    	isHuman: true,
    	printInformation() {
    		if(!this.isHuman) {
    			console.log("You are not Human :(");
    		}
    	}
    }

    console.log(person.printInformation());

    let me = Object.create(person);

    me.isHuman = false;

    console.log(me.printInformation());
    // You are not Human :(
    ```

- The #`Object.getPrototypeOf()` method returns the prototype of the specified object.

    ```jsx
    let person1 = {};

    let person2 = Object.create(person1);

    console.log(Object.getPrototypeOf(person2) === person1);
    // true

    console.log(person2 === person1);
    // false
    ```

- The #`Object.setPrototypeOf()`is same as `Object.create()`.

    ```jsx
    let animal = {
        eat: true,
        sleep: true
    }

    let animal2 = {
        eat: false
    }

    let rabbit = Object.create(animal);

    console.log(rabbit.eat);
    // true

    Object.setPrototypeOf(rabbit, animal2);

    console.log(rabbit.eat);
    // false

    console.log(rabbit.sleep);
    // undefine
    ```

- Show the `Object`information.
    - Returns property name.
        - #`Object.keys`

            ```jsx
            const object1 = {
              a: 'somestring',
              b: 42,
              c: false
            };

            console.log(Object.keys(object1));
            // expected output: Array ["a", "b", "c"]
            ```

        - #`Object.getOwnPropertyNames()`

            ```jsx
            const object1 = {
              a: 1,
              b: 2,
              c: 3
            };

            console.log(Object.getOwnPropertyNames(object1));
            // expected output: Array ["a", "b", "c"]
            ```

    - #`Object.values`returns property value.

        ```jsx
        const object1 = {
          a: 'somestring',
          b: 42,
          c: false
        };

        console.log(Object.values(object1));
        // expected output: Array ["somestring", 42, false]
        ```

    - `Object.entries()`returns both property name & value.

        ```jsx
        const object1 = {
          a: 'somestring',
          b: 42
        };

        for (const [key, value] of Object.entries(object1)) {
          console.log(`${key}: ${value}`);
        }

        // expected output:
        // "a: somestring"
        // "b: 42"
        // order is not guaranteed
        ```

- The #`Object.getOwnPropertySymbols()` method returns an array of all symbol properties found directly upon a given object.

    ```jsx
    const object1 = {};
    const a = Symbol('a');
    const b = Symbol.for('b');

    object1[a] = 'localSymbol';
    object1[b] = 'globalSymbol';

    const objectSymbols = Object.getOwnPropertySymbols(object1);

    console.log(objectSymbols.length);
    // expected output: 2
    ```

- The static #`Reflect.ownKeys()` method returns an array of the target object's own property keys.

    ```jsx
    const object1 = {
      property1: 42,
      property2: 13
    };

    const array1 = [];

    console.log(Reflect.ownKeys(object1));
    // expected output: Array ["property1", "property2"]

    console.log(Reflect.ownKeys(array1));
    // expected output: Array ["length"]
    ```

- #`obj.hasOwnProperty()` returns `true` if `Object` has its own (not inherited) key named key.

    ```jsx
    const object1 = {};
    object1.property1 = 42;

    console.log(object1.hasOwnProperty('property1'));
    // expected output: true

    console.log(object1.hasOwnProperty('toString'));
    // expected output: false

    console.log(object1.hasOwnProperty('hasOwnProperty'));
    // expected output: false
    ```

- #`Object.assign()` copy all the value from two object and transfers into one.

    ```jsx
    let object1 = { a: 1, b: 2 };
    let object2 = { b: 2, c: 3 };

    let superObj = Object.assign(object1, object2);

    console.log(object1);
    // {a: 1, b: 2, c: 3}

    console.log(object2);
    // {b: 2, c: 3}

    console.log(superObj);
    // {a: 1, b: 2, c: 3}
    ```

- `Object.fromEntries` Object from Map.

    ```jsx
    let recipeMap = new Map([
      ['cucumber', 500],
      ['tomatoes', 350],
      ['onion',    50]
    ]);
    let prices = Object.fromEntries(recipeMap);
    console.log(prices.onion);
    // 50
    ```


## Map

- Basics with `Map()`, `has()`, `get()`, & `set()`

    ```jsx
    let recipeMap = new Map([
      ['cucumber', 500],
      ['tomatoes', 350],
      ['onion',    50]
    ]);
    recipeMap.set('garilica',    60)
    		 .set('others', 100);
    console.log(recipeMap.has('others'));
    // true
    console.log(recipeMap.get('onion'));
    // 50
    ```

- Run `Map()` iterator with `keys()`, `value()` & `entries()`

    ```jsx
    let recipeMap = new Map([
      ['cucumber', 500],
      ['tomatoes', 350],
      ['onion',    50]
    ]);
    let recipeEntries = recipeMap.entries();
    console.log(recipeEntries.next().value);
    // ["cucumber", 500]
    console.log(recipeEntries.next().value);
    // ["tomatoes", 350]
    let recipeValue = recipeMap.value();
    console.log(recipeValue.next().value);
    // 500
    let recipeKeys = recipeMap.keys();
    console.log(recipeKeys.next().value);
    // "cucumber"
    ```

- Delete the `Map()` entries with `delete()` & `clear()`.

    ```jsx
    let recipeMap = new Map([
      ['cucumber', 500],
      ['tomatoes', 350],
      ['onion',    50]
    ]);
    recipeMap.delete()
    console.log(recipeMap.size);
    // 2
    recipeMap.clear()
    console.log(recipeMap.size);
    // 0
    ```

- Length of `Map()` with `size`.

    ```jsx
    let recipeMap = new Map([
      ['cucumber', 500],
      ['tomatoes', 350],
      ['onion',    50]
    ]);
    console.log(recipeMap.size);
    // 3
    ```

- Random Number with `Math.random()`

    ```jsx
    // With ceil
    for (let i = 0; i < 9; i = Math.ceil(Math.random() * 10)) {
        console.log(i);
    }
    // With floor (only goes to 0 to 9)
    for (let i = 0; i < 9; i = Math.floor(Math.random() * 10)) {
        console.log(i);
    }
    ```


## Math

- `Math` is a built-in object that has properties and methods for mathematical constants and functions. It’s not a function object.

    [Math](The%20JavaScript%20language%20dda21ff2e0dc4987a0af85b5e6efb600/Math%20d81dc67853fc4521a32f51d9ff504b89.csv)


## Number

- Fixed the Float number `toFixed()`

    ```jsx
    let n = 1.23456;
    alert( n.toFixed(2) ); // 1.23
    ```


## String

- Escape notation
    - `\n`New line
    - `\r`Carriage return: not used alone. Windows text files use a combination of two characters \r\n to represent a line break.
    - `\', \"`Quotes
    - `\\`Backslash
    - `\t`Tab
    - `\b, \f, \v` Backspace, Form Feed, Vertical Tab – kept for compatibility, not used nowadays.
    - `\xXX`Unicode character with the given hexadecimal Unicode XX, e.g. '\x7A' is the same as 'z'.
    - `\uXXXX`A Unicode symbol with the hex code XXXX in UTF-16 encoding, for instance \u00A9 – is a Unicode for the copyright symbol :copyright:. It must be exactly 4 hex digits.
    - `\u{X…XXXXXX}` **(1 to 6 hex characters)** A Unicode symbol with the given UTF-32 encoding. Some rare characters are encoded with two Unicode symbols, taking 4 bytes. This way we can insert long codes.
- `padStart` and takes the desired length and padding character as arguments.

    ```jsx
    console.log(String(6).padStart(3, "0"));
    // → 006
    ```

- Make Array a String with `toString`.

    ```jsx
    console.log([1, 2].toString());
    // 1,2
    ```

- Search for a specific value with `lastIndexOf` & `indexOf`

    ```jsx
    let num = [1, 2, 3, 2, 1];
    console.log(num.indexOf(2));
    // 1
    console.log(num.lastIndexOf(1));
    // 4
    console.log("coconut".indexOf("co"));
    // 0
    console.log("coconut".indexOf("co", 1))
    // 3
    ```

- Split the string with `split`.

    ```jsx
    let sentence = "Secretarybirds.specialize.in.stomping";
    let words = sentence.split(".");
    console.log(words);
    // → ["Secretarybirds", "specialize", "in", "stomping"]
    console.log(words.join(". "));
    // → Secretarybirds. specialize. in. stomping
    ```

- Upper and Lowercase with `toUpperCase()` & `toLowerCase`.

    ```jsx
    let word = "This is Upper Case";
    console.log(word.toUpperCase());
    // THIS IS UPPER CASE
    let word = "This is Lower Case";
    console.log(word.toLowerCase());
    // this is lower case
    ```

- Remove whitespace with `trim`.

    ```jsx
    console.log("  okay \n ".trim());
    // → okay
    ```

- Repeated with `repeat`

    ```jsx
    console.log("/" + "*".repeat(10) + "\n" + "@Gii\n" + "*".repeat(10) + "/");
    /**********
    @Gii
    **********/
    ```

- To get a character at position with `charAt()`

    ```jsx
    let str = "hello"
    console.log(str[1]);
    // 1
    console.log(str.charAt(1));
    // 1
    ```

- Check if it contains the string in start and end with `startWith()` & `endWith()`.

    ```jsx
    alert( "Widget".startsWith("Wid") );
    // true
    alert( "Widget".endsWith("get") );
    // true
    ```

- Checks every array with `every()`.

    ```jsx
    const formula = n => n % 2 === 0;
    [2, 4, 6, 8, 10].every(formula);
    // true
    [2, 3, 6, 8, 10].every(formula);
    // false
    ```

- Change value of array with `splice()`.

    ```jsx
    const meetingWords = ["hi", "hello", "whats up", "how are you"];
    const newMeetingWords = ["ohh hello", "nice to meet you"]
    meetingWords.splice(1, 2, newMeetingWords);
    console.log(meetingWords);
    // ["hi", ["ohh hello", "nice to meet you"], "how are you"]
    ```

- Combine array in the array with `flat()`.

    ```jsx
    onst meetingWords = ["hi", ["ohh hello", "nice to meet you"], "how are you"];
    console.log(meetingWords.flat());
    // ["hi", "ohh hello", "nice to meet you", "how are you"]
    ```

- Manipulate Arrays with `push()` & `pop()`.

    ```jsx
    let num = [1, 2, 3];
    num.push(4);
    // Adds 4 in last in seqnce
    console.log(num);
    // [1, 2, 3, 4]
    console.log(num.pop()); // Delete's the 4 for seqnce
    // 4
    console.log(num);
    // [1, 2, 3]
    ```

- Changes all elements in an array to a static value with `fill()`.

    ```jsx
    const array1 = [1, 2, 3, 4];
    const i = array1.indexOf(2);
    console.log(array1.fill("hi", i));
    // [1, "hi", "hi", "hi"]
    console.log(array1.fill("hi", i, i+1));
    // [1, "hi", 3, 4]
    ```
    ### `forEach()` inline loop
    ```js
    ["A", "B"].forEach(l => console.log(l));
    // A
    // B
    ```

- `filter()` to `if()` in inline.

    ```jsx
    const numArray = [1, 2, 3, 4, 5];
    console.log(numArray.filter(n => n%2 === 0));
    // [2, 4]
    ```

- `map()` creates a new array.

    ```jsx
    const array1 = [1, 4, 9, 16];
    const map1 = array1.map(x => x * 2);
    console.log(map1);
    // Array [2, 8, 18, 32]
    ```

- `some()` to find `true` & `false`.

    ```jsx
    const array = [1, 2, 3, 4, 5];
    console.log(array.some(l => l % 2 == 0));
    // true
    ```

- Shallow copies part of an array to another location `copyWithin()`.

    ```jsx
    const array1 = ['a', 'b', 'c', 'd', 'e'];
    console.log(array1.copyWithin(0, 3, 4));
    // ["d", "b", "c", "d", "e"]
    // copy to index 1 all elements from index 3 to the end
    console.log(array1.copyWithin(1, 3));
    // ["d", "d", "e", "d", "e"]
    ```

- Inline calculation `reduce()`.

    ```jsx
    const array1 = [1, 2, 3, 4];
    const reducer = (a, b) => a + b;
    console.log(array1.reduce(reducer));
    // 10
    console.log(array1.reduce(reducer, 5));
    // 15
    ```

- Combine value with `concat()`.

    ```jsx
    let arrays = [[1, 2, 3], [4, 5], [6]];
    console.log(arrays.reduce((a, b) => a.concat(b)))
    // [1, 2, 3, 4, 5, 6]
    ```


## Global Object

- The `WeakSet` object lets you store weakly held objects in a collection.

    ```jsx
    // WeakSet
    let visitedSet = new WeakSet();
    let john = { name: "John" };
    visitedSet.add(john);
    console.log(visitedSet.has(john));
    // true
    john = null;
    console.log(visitedSet.has(john));
    // fase
    // Set
    visitedSet = new Set();
    visitedSet.add(john);
    john = { name: "John" };
    console.log(visitedSet.has(john));
    // true
    john = null;
    console.log(visitedSet.has(john));
    // true
    ```

- The `WeakMap` object is a collection of key/value pairs in which the keys are weakly referenced. The keys must be objects and the values can be arbitrary values.

    ```jsx
    // :file_folder: cache.js
    let cache = new Map();
    // calculate and remember the result
    function process(obj) {
      if (!cache.has(obj)) {
        let result = /* calculations of the result for */ obj;
        cache.set(obj, result);
      }
      return cache.get(obj);
    }
    // Now we use process() in another file:
    // :file_folder: main.js
    let obj = {/* let's say we have an object */};
    let result1 = process(obj); // calculated
    // ...later, from another place of the code...
    let result2 = process(obj); // remembered result taken from cache
    // ...later, when the object is not needed any more:
    obj = null;
    alert(cache.size); // 1 (Ouch! The object is still in cache, taking memory!)
    ```

- Convert string into number with `parseInt`.

    ```jsx
    function input(value) {
    	let valueInt = parseInt(value);
    	return valueInt * 2;
    }
    console.log(input(3));
    // 6
    ```


## Symbol

- Symbol into Method.

    ```jsx
    let sym = Symbol("123");
    let met = {
    	[sym]() {return "This is Symbol"}
    }
    console.log(met[sym]());
    ```

- Global symbols with `Symbol.for()`.

    ```jsx
    let id = Symbol.for("id");
    let idAgain = Symbol.for("id");
    console.log( id === idAgain );
    // true
    ```

- Global symbol key with `Symbol.keyFor()`.

    ```jsx
    et id = Symbol.for("id");
    console.log( Symbol.keyFor(id));
    // id
    ```

- The iterator interface in `Symbol.iterator()`

    ```jsx
    let word = "in";
    let ite = word[Symbol.iterator]();
    console.log(ite.next());
    // {value: "i", done: false}
    console.log(ite.next().value);
    // n
    console.log(ite.next());
    // {value: undefined, done: true}
    console.log(ite.next().done);
    // true
    let array = ["inside", "outside"];
    ite = array[Symbol.iterator]();
    console.log(ite.next().value);
    // inside
    ```


## Error

- Extending Error

    ```jsx
    class TrueError extends Error {
        constructor(name, message) {
            super(message);
            this.name = name;
        }
    }

    try {
        test();
    } catch(err) {
        if ( err instanceof TrueError) {
            console.log( err.name );
        }
        if ( err instanceof Error ) {
            console.log( err.message );
        }
    } finally {
        console.log("Runed");
    }

    // TrueError
    // Not a real error.
    // Runed
    ```

- ❓Extending Error can `extends`other error also

    ```jsx
    class FormatError extends SyntaxError {
        constructor(message) {
            super(message);
            this.name = "FormatError";
            this.stack = "Stack";
        }
    }

    let err = new FormatError("Formatting error");

    alert( err.message ); // Formatting error
    alert( err.name ); // FormatError
    alert( err.stack ); // stack

    alert( err instanceof FormatError ); // true
    alert( err instanceof SyntaxError ); // true (because inherits from SyntaxError)
    ```

- Error with `if...else`

    ```jsx
    try {
        NotDefine();
    } catch(err) {
        console.log( err.name === "ReferenceError" );
    }

    // true
    ```


# Class

- What class `User {...}` construct really does is:
    1. Creates a function named `User`, that becomes the result of the class declaration. The function code is taken from the `constructor` method (assumed empty if we don’t write such method).
    2. Stores class methods, such as `sayHi`, in `User.prototype`.

    ```jsx
    class User{
        constructor(name, age) {
            this.name = name;
            this.age = age;
        }
        userInfo() {
            console.log(`Name: ${this.name}\n Age: ${this.age}`);
        }
    }

    let jone = new User("Jone Funzo", 30);

    console.log(jone.age);
    // 30

    console.log(jone.userInfo());
    // Name: Jone Funzo
     Age: 30
    ```

- Just like functions, classes can be defined inside another variable expression, passed around, returned, assigned, etc.

    ```jsx
    const Use = class {
        constructor(name) {
            this.name = name;
        }
        sayHi() {
            console.log(this.name);
        }
    }

    let use = new Use("Jonney");

    use.sayHi()
    // Jonney
    ```

- Class with also having function expression with it.

    ```jsx
    class User {
        constructor(name) {
            this.name = name;
        }
        sayHi(age) {
            console.log(this.name + ' ' + age);
        }
    }

    let me = new User("James");

    console.log(me.sayHi(32));
    // James 32
    ```

- Function with `class` inside it.

    ```jsx
    function makeClass(word) {
    	return class {
    		sayHi() {
    		console.log(word);
    		}
    	}
    }

    let hello = new makeClass("How are you?");

    hello().sayHi();
    // How are you?
    ```

- #`getter` & #`setter`in the class.

    ```jsx
    class User {
        constructor(name) {
            this.name = name;
        }
        get name() {
            return this._name;
        }
        set name(value) {
            if (value > 4) {
                return "Too short name!";
            }
            this._name = value;
        }
    }

    let user = new User("Jone");

    user.name
    ```

- Using `class`without `constructor`.

    ```jsx
    class User {
    	name = "Joey";
    	age = 32;

    	info() {
    		console.log(`${this.name} age is ${this.age}`);
    	}
    }

    let joey = new User;

    console.log(joey.name);
    // Joey

    console.log(joey.info());
    // Joey age is 32
    ```

- #`extents`information.
    - `extents`to connect two classes together.

        ```jsx
        class Animal {
            constructor(name) {
                this.name = name;
            }
            walk() {
                console.log(`${this.name} can walk.`);
            }
        }

        class Birds extends Animal {
            fly() {
                console.log(`${this.name} can fly`);
            }
        }

        let lion = new Animal("Lion");
        console.log(lion.walk());
        // Lion can walk
        // console.log(lion.fly()); woldn't run
        // Error

        let pigions = new Birds("Pigions");
        console.log(pigions.walk());
        // Pigions can walk
        console.log(pigions.fly());
        // Pigions can fly
        ```

    - #`super.variable`shows the `extents`prenat variable result.
        - `super`don't work with arrow function(`⇒`).

        ```jsx
        class Animal {
            constructor(name) {
                this.name = name;
            }
            place() {
                return `Londan`;
            }
        }

        class Rabbit extends Animal {
            place() {
                return `Londan`;
            }
            travel() {
                console.log(`${this.place()} to ${super.place()}`);
            }
        }

        let rabbit = new Rabbit("Jonney");

        rabbit.travel();
        ```

    - `extents` connect with `super()`to bypass parental `constructor`.

        ```jsx
        class Animal {
            constructor(name) {
                this.speed = 0;
                this.name = name;
            }
        }

        class Reddit extends Animal {
            constructor(name, age) {
                super(name);
                this.age = age;
            }
            run() {
                console.log(`That ${this.name} is ${this.age} age and running.`);
            }
        }

        let reddit = new Reddit("White Rabbit", 23);

        reddit.run()
        // That White Rabbit is 23 age and running.
        ```

- Private properties and methods to secure the overwriting.

    ```jsx
    class Cla {
        #private = 0;

        #privateMessage() {
            console.log("You unlock it WoW.");
        }

        lockMessage() {
            console.log(this.#privateMessage());
        }
    }

    let cla = new Cla;

    cla.lockMessage();
    // You unlock it WoW.

    console.log(cla.private);
    // Error

    console.log(cla.privateMessage());
    // Erro
    ```

- Classes with built-in classes.

    ```jsx
    class PowerArray extends Array {
        number = 20;

        add() {
            return 2 + 2;
        }
    }

    let powerArray = new PowerArray(1, 2, 3, 4);

    console.log(powerArray.length);
    // 4

    console.log(powerArray.number);
    // 20

    console.log(powerArray.add());
    // 4
    ```

- Make the mixin with object and use with class.

    ```jsx
    // Mixin
    let myMixin = {
    	sayUser(name) {
    		console.log(`${name} is ${this.age} years old.`);
    	}
    }

    class Jonney {
    	age = 32;
    	test = true;
    }

    Object.assign(Jonney.prototype, myMixin);

    let jonney = new Jonney();

    jonney.sayUser("Jonney");
    // Jonney
    console.log(jonney.test);
    // true
    ```

- `static`methods are called directly on the class without creating an instance/object of the class.

    ```jsx
    class Car {
    	static myCars(name) {
    		console.log(name);
    	}
    	static NumCars = 3;
    }

    console.log(Car.NumCars = 4);
    // 4

    Car.myCars("Ford");
    ```

- #`Symbol.hasInstance`is well-known symbol is used to determine if a constructor object recognizes an object as its instance.

    ```jsx
    class TrueOr {
        static [Symbol.hasInstance](obj) {
            return true;
        }
    }

    obj = {
        eat: false
    }

    console.log(obj instanceof TrueOr);
    // true

    console.log(Array instanceof TrueOr);
    // true

    class TrueOr {
        static [Symbol.hasInstance](obj) {
            if(obj.eat) return true; // changed
        }
    }

    cosnole.log(obj instanceof TrueOr);
    // true
    ```


# Expressions and operators

- The #`new` syntax
    - The function is created with the arguments `arg1...argN` and the given function Body.

        ```jsx
        let sum = new Function('a', 'b', 'return a + b');

        alert( sum(1, 2) ); // 3
        ```

    - When a function is created using a new Function, its `[[Environment]]` is set to reference not the current Lexical Environment, but the global one.

        ```jsx
        function getFunc() {
          let value = "test";

          let func = new Function('alert(value)');

          return func;
        }

        getFunc()(); // error: value is not defined
        ```

    - Turn `function` into `Object`.

        ```jsx
        function User(name, age) {
        	this.name = name;
        	this.age = age;
        }

        let ravi = new User("Ravi Sharma", 25);

        console.log(ravi.name);
        // Ravi Sharma
        ```

- #`instanceof`check whether an object belongs to a certain class or not.

    ```jsx
    console.log([] instanceof Array);
    // true

    console.log({} instanceof Symbol);
    // false

    console.log(Array instanceof Object);
    // true
    ```

- Change the location of function with `this` & `call`.

    ```jsx
    function speak(line) {
      console.log(`The ${this.type} rabbit says '${line}'`);
    }
    let hungryRabbit = {type: "hungry", speak};
    hungryRabbit.speak("I could use a carrot right now.");
    // The hungry rabbit says 'I could use a carrot right now.'
    speak.call(hungryRabbit, "Burp!");
    // → The hungry rabbit says 'Burp!'
    ```

- Optional chaining with `?.`

    ```jsx
    const user = {
    	name = "aav";
    }
    console.log(user?.name);
    // aav
    console.log(user?.age);
    // undefine
    ```

- Converts number-string to number with `+`

    ```jsx
    console.log(+true);
    // 1
    console.log(+false);
    // 0
    let x = "1", y = "2";
    console.log(x + y);
    // 12
    console.log(+x + +y);
    // 3
    ```

- `~` Adds +1 in the number.

    ```jsx
    console.log(~1);
    // 2
    ```


# Statements and declarations

- `import` & `export`
    - Module import with `require()`

        ```jsx
        // sayHi.js
        function sayHi(user) {
        	return `Hello ${user}`;
        }

        module.exports = { sayHi };
        ```

        ```jsx
        // main.js

        let hi = require('./say');

        console.log(hi.sayHi("AAV"));
        ```

    - Normal module

        ```jsx
        // 📁 sayHi.js
        export function sayHi(user) {
          alert(`Hello, ${user}!`);
        }
        ```

        ```jsx
        // 📁 main.js
        import {sayHi} from './sayHi.js';

        alert(sayHi); // function...
        sayHi('John'); // Hello, John!
        ```

    - HTML file Module

        ```jsx
        // main.js

        export function sayHi(user) {
        	return `Hello ${user}`;
        }
        ```

        ```html
        <!Doctype HTML>
        <body>
        	<script type="module">
        		import { sayHi } from './main.js'

        		document.body.innerHTML = sayHi("AAV");
        	</script>
        </body>
        ```

    - if a module script is fetched from another origin, the remote server must supply a header `Access-Control-Allow-Origin` allowing the fetch.
    - The `import.meta` object exposes context-specific metadata to a JavaScript module. It contains information about the module.

        ```html
        <!--index.html-->

        <script type="module" src="my-module.js"></script>
        ```

        ```jsx
        // my-module.js

        console.log(import.meta);
        ```

    - `import.meta.url` for showing URL.

        ```html
        <script type="module">
          alert(import.meta.url); // script url (url of the html page for an inline script)
        </script>
        ```

    - `export`and `import`multipule module.

        ```jsx
        // export.js

        function sayHi(name) {
        	console.log(`Hello ${name}`);
        }

        let days = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];

        let user = {
        	name: 'Peater Sons',
        	year: 2003
        }

        export { sayHi, days, user }
        ```

        ```jsx
        // import.js

        import { sayHi, days, user } from './export.js';

        sayHi(user.name);

        console.log(`This is ${days[3]}day of the month.`)
        ```

    - `import *` for importing as object **Note**: This is preferred method to import the module.

        ```jsx
        // export.js

        function sayHi(name) {
        	console.log(`Hello ${name}`);
        }

        let days = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];

        let user = {
        	name: 'Peater Sons',
        	year: 2003
        }

        export { sayHi, days, user }
        ```

        ```jsx
        // import.js

        import * as data from './export.js';

        data.sayHi(data.user.name);

        console.log(`This is ${data.days[3]}day of the month.`);
        ```

    - **Note**: To avoid that and keep the code consistent, there’s a rule that imported variables should correspond to file names.

        ```jsx
        import User from './user.js';
        import LoginForm from './loginForm.js';
        import func from '/path/to/func.js';
        ```

    - Change name with `as`

        ```jsx
        // export.js

        export class User {
        	constructor(name) {
        		this.name = name;
        	}
        }

        export function sayHi(user) {
        	console.log(`Hello, ${user}!`);
        }
        ```

        ```jsx
        // import.js

        import { User as user, sayHi as hi } from './export.js';

        let id = new user('John');

        hi(id.name);
        ```

    - `import` anywhere in the script with Dynamic imports

        ```jsx
        // export.js

        function hello() {
        	console.log(`Hello`);
        }

        function bye() {
        	console.log(`Bye`);
        }

        export { hello, bye };
        ```

        ```jsx
        // import .js

        let { hello, bye } = await import('./export.js');

        hello();
        bye();
        ```

- Generator functions with `function*` & `yield`
    - How to Generator looks?

        ```jsx
        function* generatorSequence() {
            yield 1;
            yield 2;
            return 3;
        }

        let generator = generatorSequence(); // Important to declare or not work

        let one = generator.next();
        console.log(one);
        // {value: 1, done: false}

        let two = generator.next();
        console.log(two);
        // {value: 2, done: false}

        let three = generator.next();
        console.log(three);
        // {value: 3, done: true}
        ```

    - Generator with loop.

        ```jsx
        function* foo(index) {
            let loop = 0;
            for ( ; loop < index; loop++ ) {
                yield loop;
            }
            return loop;
        }

        let runner = foo(3);

        console.log(runner.next());
        console.log(runner.next());
        console.log(runner.next());
        console.log(runner.next());
        ```

    - Generator with loop with `for...of`

        ```jsx
        function foo(index) {

        	let loop = 0;

        	for ( ; loop < index ; loop++ ) {
        		yield loop;
        	}

        	return loop;
        }

        for ( let value of foo(5) ) {
        	console.log(value);
        }
        /*
        1
        2
        3
        4
        Don't reutrn `done: true`
        */
        ```

    - Generator with spread syntax.

        ```jsx
        function* foo(index) {

        	let loop = 0;

        	for ( ; loop < index ; loop++ ) {
        		yield loop;
        	}

        	return loop;
        }

        console.log(...foo(5));

        // 0, 1, 3, 4
        ```

    - The composed generator:

        ```jsx
        function* generatePasswordCodes() {
            for ( let start = 48; start <= 57; start++) yield start;
            for ( let start = 65; start <= 90; start++) yield start;
            for ( let start = 97; start <= 122; start++) yield start;
        }

        let str = ''

        for ( let code of generatePasswordCodes() ) {
            str += String.fromCharCode(code);
        }

        console.log(str);
        // 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
        ```

    - Show `console.log`first and then answer.

        ```jsx
        function* gen() {
            console.log("Slove");

            let ask1 = yield "2 + 2 = ?";

            console.log(ask1);

            let ask2 = yield "3 + 3 = ?";

            console.log(ask2);
        }

        let generator = gen();

        console.log(generator.next().value);
        // Slove
        // 2 + 2 = ?
        console.log(generator.next(4).value);
        // 4
        // 3 + 3 = ?
        console.log(generator.next(9).done);
        // 9
        // true
        ```

    - `*[Symbol.iterator]`

        ```jsx
        let range = {
        	from: 1,
        	to: 5,

        	*[Symbol.iterator]() {
        		for( let value = this.from; value <= this.to; value++ ) {
        			yield value;
                }
            }
        }

        console.log(...range);
        // 1, 2, 3, 4, 5
        ```

    - `generator.throw`for Error

        ```jsx
        function* gen() {
          try {
            let result = yield "2 + 2 = ?"; // (1)

            alert("The execution does not reach here, because the exception is thrown above");
          } catch(e) {
            alert(e); // shows the error
          }
        }

        let generator = gen();

        let question = generator.next().value;

        generator.throw(new Error("The answer is not found in my database")); // (2)
        ```

    - Generator for random number.

        ```jsx
        function* pseudoRandom(value) {
            while(true) {
                value = value * 16807 % 2147483647;
                yield value;
            }
        }

        let generator = pseudoRandom(1);

        alert(generator.next().value); // 16807
        alert(generator.next().value); // 282475249
        alert(generator.next().value); // 1622650073
        ```

    - `async`Async iterable range iterable range

        ```jsx
        let range = {
        	from: 1,
        	to: 5,

        	async *[Symbol.asyncIterator]() {
        		for ( let value = this.from; value <= this.to; value++ ) {
        			await new Promise(reslove => setTimeout(reslove, 1000));
        			yield value;
                }
        	}
        };

        (async () => {
        	for await ( let value of range ) console.log(value);
        })()
        /*
        1
        2
        3
        4
        5
        Prints ever 1s
        */
        ```

- #`await`& `async`
    - `async` a function always returns a promise.

        ```jsx
        async function f() {
            return 1;
        }

        f().then(message => console.log(message));
        ```

    - It can also use with `class`.

        ```jsx
        class fuc {
        	async f() {
        		return await Promise.resolve(1);
        	}
        }

        new fuc()
        	.f()
        	.then(reslove => console.log(reslove));
        ```

    - `await` makes JavaScript wait until that promise settles and returns its result.

        ```jsx
        async function f() {

            let promise = new Promise((reslove, reject) => reslove(1));

            let fun = await promise;

            return fun;
        }

        f().then(reslove => console.log(reslove));
        // 1
        ```

    - `await`can't work without `async`

        ```jsx
        function f() {
          let promise = Promise.resolve(1);
          let result = await promise; // Syntax error
        }
        ```

    - Error handling

        ```jsx
        async function f() {
            let response = await fetch("https://it-is-error");
        }

        f().catch(console.log);
        ```

    - ❓ `async/await`instad of `Promise`

        ```jsx
        async function info(username, ...data_type) {

            console.log(data_type);
            let response = await fetch(`https://api.github.com/users/${username}`);
            let user = await response.json();

            if (data_type.includes("name")) console.log(`Name: ${user.name}`);
            if (data_type.includes("repo")) console.log(`Repos: ${user.public_repos}`);
            if (data_type.includes("url")) console.log(`URL: ${user.url}`);

        }
        ```

    - ❓ Rewrite this example code from the chapter Promises chaining using async/await instead of .then/catch.

        ```jsx
        async function loadJson(url) {
            let response = await fetch(url);
            if ( response.status == 200 ) {
                return response.json();
            } else {
                throw new Error(response.status);
            }
        }

        loadJson('no-such-user.json')
          .catch(alert);
        ```

    - ❓ Rewrite "rethrow" with async/await

        ```jsx
        async function loadJson() {

            let name = prompt("Enter a name?");

            let response = await fetch(`https://api.github.com/users/${name}`);
            let user = await response.json()

            if (response.status == 404) {
                alert("No such user, please reenter.");
                return loadJson();
            }

            alert(`Full name: ${user.name}.`);
            return user;
        }

        ```

- `throw`catches error.

    ```jsx
    new Promise((reslove, reject) => {
    	throw new SyntaxError("Nothing")
    })
    	.catch(error => console.log(error.name));
    ```

- #`try...catch`
    - `try...catch` that allows us to “catch” errors so the script can, instead of dying, do something more reasonable.

        ```jsx
        try {
            console.log("run");
            try {
                NotDefine();
            } catch (error) {
                console.log("Error the function is not define.");
            }
        } catch (err) {
            console.log("I don't know why error is here.");
        }
        // run
        // Error the function is not define.

        ```

    - `try...catch`expression can compare with `instaceOf`.

        ```jsx
        try {
            NotDefine();
        } catch(err) {
            if ( err instanceof ReferenceError ) {
                console.log(err.name);
            }
        }
        ```

    - Show error message in `catch`.

        ```jsx
        try {
        	NotAFunction();
        } catch (e) {
        	console.log(`${e} \n\t is not a function`);
        }
        ```

    - #`try…catch…finally`finally will always run even there was no error.

        ```jsx
        function func() {

          try {
            if (confirm("Do you want error?")) error();
            return "No Error"
          } catch (err) {
            return "Error";
          } finally {
            console.log("Completed and Resual is:");
          }
        }

        console.log( func() );

        // true
        /*
        Completed and Resual is:
        Error
        */

        // false
        /*
        Completed and Resual is:
        No Error
        */
        ```

    - `try...finally`you can also run.

        ```jsx
        function func() {

          try {
            if (confirm("Do you want error?")) error();
            return "No Error"
          } finally {
            console.log("Completed and Resual is:");
          }
        }

        // true
        /*
        Completed and Resual is:
        */

        // false
        /*
        Completed and Resual is:
        No Error
        */
        ```

    - Error object
        - Error `name`shows the name of the error.

            ```jsx
            try {
            	NoAObject()
            } catch (e) {
            	console.log(e.name);
            }
            // ReferenceError
            ```

        - Error `message`textual message about error details.

            ```jsx
            try {
            	NotAObject();
            } catch (e) {
            	console.log(e.message);
            }
            // NotAObject is not defined
            ```

        - Error `stack`: a string with information about the sequence of nested calls that led to the error. Used for debugging purposes.

            ```jsx
            try {
            	NotAObject();
            } catch (e) {
            	console.log(e.stack);
            }

            /*
            	ReferenceError: NotAObject is not defined
            	    at <anonymous>:2:2
            */
            ```


# Web APIs

## Fetch

- `fetch`use web api in json.

    ```jsx
    let userName = prompt("What is your username?", "aav");

    fetch(`https://api.github.com/users/${userName}`)
        .then(github => github.json())
        .then(github => console.log(github.public_repos));
    ```


## GlobalEventHandlers

- The `onerror` property of the `GlobalEventHandlers` mixin is an `EventHandler` that processes error events.

    ```jsx
    <script>
      window.onerror = function(message, url, line, col, error) {
        alert(`${message}\n At ${line}:${col} of ${url}`);
      };

      function readData() {
        badFunc(); // Whoops, something went wrong!
      }

      readData();
    </script>
    ```


## Window Or WorkerGlobalScope

- ❓ Write a function printNumbers(from, to) that outputs a number every second, starting from and ending with to. Using `setTimeout` & `setInterval`.
    - `setTimeout`

    ```jsx
    function printNumbers(from, to) {
        setTimeout(function get() {
            console.log(from++);
            if(from < to) setTimeout(get(), 1000);
        }, 5000);
    }

    printNumbers(1, 5);
    /*
    1
    2
    3
    4
    5
    */
    ```

    - `setInterval`

    ```jsx
    function printNumbers(from, to) {
        timeId = setInterval(() => {
            console.log(from++);
            if(from > to) clearInterval(timeId);
        }, 1000);
    }
    /*
    1
    2
    3
    4
    5
    */
    ```

- ❓ Display Time Every 3 Second

    ```jsx
    function showTime() {

        // return new date and time
        let dateTime= new Date();

        // returns the current local time
        let time = dateTime.toLocaleTimeString();

        console.log(time)

        // display the time after 3 seconds
         setTimeout(showTime, 3000);
    }

    // calling the function
    showTime(); // Shows the output every 3 seconds
    ```

- The #`setInterval()` method calls a function or evaluates an expression at specified intervals (in milliseconds).

    ```jsx
    // repeat with the interval of 2 seconds
    let timerId = setInterval(() => alert('tick'), 2000);

    // after 5 seconds stop
    setTimeout(() => { clearInterval(timerId); alert('stop'); }, 5000);
    ```

- `clearInterval()` clear the `setInterval()` execution.

    ```jsx
    // repeat with the interval of 2 seconds
    let timerId = setInterval(() => alert('tick'), 2000);

    // after 5 seconds stop
    setTimeout(() => { clearInterval(timerId); alert('stop'); }, 5000);
    ```

- #`setTimeout` allows us to run a function once after the interval of time.
    - What will setTimeout show?

        ```jsx
        let i = 0;

        setTimeout(() => alert(i), 100); // ?

        // assume that the time to execute this function is >100ms
        for(let j = 0; j < 100000000; j++) {
          i++;
        }
        ```

        ▶️ Answer

        ```jsx
        let i = 0;

        setTimeout(() => alert(i), 100); // 100000000

        // assume that the time to execute this function is >100ms
        for(let j = 0; j < 100000000; j++) {
          i++;
        }
        ```

    - `setTimeout()` don't work with `this`

        ```jsx
        let user = {
          firstName: "John",
          sayHi() {
            alert(`Hello, ${this.firstName}!`);
          }
        };

        setTimeout(user.sayHi, 1000); // Hello, undefined!
        ```

        - Solution

        ```jsx
        let user = {
          firstName: "John",
          sayHi() {
            alert(`Hello, ${this.firstName}!`);
          }
        };

        setTimeout(function() {
          user.sayHi(); // Hello, John!
        }, 1000);
        ```

- `clearTimeout()` clears the `setTimout()` execution.

    ```jsx
    for (let run = 1; run < 5; run++) {
        if (run < 3 ) {
            const runTime = setTimeout(() => {
                console.log(`Running ${run}`);
            }, 10);
        } else {
            clearTimeout(runTime);
        }
    }

    // Running 1
    // Running 2
    ```

- `setImmediate()` will always execute before setTimeout and setImmediate. It is same as `setTimeout(callback,0)`.

    ```jsx
    eEmitter.on("event1", (a, b) => {
      setImmediate(() => {
        console.log(`${a} ${b}`);
      });
    });
    eEmitter.on("event2", (a, b) => {
      console.log(`${a} ${b}`);
    });

    for (let x = 0; x < 4; x++) {
      eEmitter.emit("event1", x, "b1");
      eEmitter.emit("event2", x, "b2");
    }

    // 0 b2
    // 1 b2
    // 2 b2
    // 3 b2
    // 0 b1
    // 1 b1
    // 2 b1
    // 3 b1
    ```


## Console

- The `console.dir()` displays an interactive list of the properties of the specified JavaScript object.

    ```jsx
    console.dir(Number);
    /*
    ƒ Number()
    	EPSILON:
    	2.220446049250313
    	e-16
    	MAX_SAFE_INTEGER: 9007199254740991
    	MAX_VALUE:
    	1.7976931348623157
    	e+308
    	MIN_SAFE_INTEGER: -9007199254740991
    	MIN_VALUE:
    	5
    	e-324
    	NEGATIVE_INFINITY: -Infinity
    	NaN: NaN
    	POSITIVE_INFINITY: Infinity
    	arguments: (...)
    	caller: (...)
    	isFinite: ƒ isFinite()
    	isInteger: ƒ isInteger()
    	isNaN: ƒ isNaN()
    	isSafeInteger: ƒ isSafeInteger()
    	length: 1
    	name: "Number"
    	parseFloat: ƒ parseFloat()
    	parseInt: ƒ parseInt()
    	prototype: Number {0, constructor: ƒ, toExponential: ƒ, toFixed: ƒ, toPrecision: ƒ, …}
    	__proto__: ƒ ()
    	[[Scopes]]: Scopes[0]
    */
    ```

- The `console.log()`shows the output in console.

    ```jsx
    cosnole.log("Hello World");
    // Hello World
    ```

- The `console.log()` shows object in table.

    ```jsx
    console.table({
      aman: {
        age: 18,
        location: "Mumbai",
        country: "India",
      },
      shile: {
        age: 15,
        location: "punjab",
        country: "India",
        dateOfYear: 2015,
      },
    });
    // ┌─────────┬─────┬──────────┬─────────┬────────────┐
    // │ (index) │ age │ location │ country │ dateOfYear │
    // ├─────────┼─────┼──────────┼─────────┼────────────┤
    // │  aman   │ 18  │ 'Mumbai' │ 'India' │            │
    // │  shile  │ 15  │ 'punjab' │ 'India' │    2015    │
    // └─────────┴─────┴──────────┴─────────┴────────────┘
    ```

- The `console.clear()` clears the output in the console.

    ```jsx
    console.log("Hello World");
    console.clear();
    console.log("Bye World");

    // Bye World
    ```
