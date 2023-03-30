# Browser: Document, Events, Interfaces

# Document

## document.documentElement

## document.body

- You can only but document.body in <body> tag.

    ```html
    <html>

    <head>
      <script>
        alert( "From HEAD: " + document.body ); // null, there's no <body> yet
      </script>
    </head>

    <body>

      <script>
        alert( "From BODY: " + document.body ); // HTMLBodyElement, now it exists
      </script>

    </body>
    </html>
    ```

- `document.body.style`

    ```jsx
    // change the background color to red
    document.body.style.background = "red";

    // change it back after 1 second
    setTimeout(() => document.body.style.background = "", 1000);
    ```


## document.head

## Searching:

- Live collections of **getElementsBy*** & **querySelector***
    - All methods "getElementsBy*" return a live collection. Such collections always reflect the current state of the document and “auto-update” when it changes.

    ```html
    <div>First div</div>

    <script>
      let divs = document.getElementsByTagName('div');
      alert(divs.length); // 1
    </script>

    <div>Second div</div>

    <script>
      alert(divs.length); // 2
    </script>
    ```

    - In contrast, querySelectorAll returns a static collection. It’s like a fixed array of elements.

    ```html
    <div>First div</div>

    <script>
      let divs = document.querySelectorAll('div');
      alert(divs.length); // 1
    </script>

    <div>Second div</div>

    <script>
      alert(divs.length); // 1
    </script>
    ```

- There are 6 main methods to search for nodes in DOM:

    [Methods to Search](Browser%20Document,%20Events,%20Interfaces%205b1ea1234a324530a62e17f0aecee387/Methods%20to%20Search%20bae8734b53c44a51833cba491564ef97.csv)

- ❓ Search for elements

    ```jsx
    // 1. The table with `id="age-table"`.
    let table = document.getElementById('age-table')

    // 2. All label elements inside that table
    table.getElementsByTagName('label')
    // or
    document.querySelectorAll('#age-table label')

    // 3. The first td in that table (with the word "Age")
    table.rows[0].cells[0]
    // or
    table.getElementsByTagName('td')[0]
    // or
    table.querySelector('td')

    // 4. The form with the name "search"
    // assuming there's only one element with name="search" in the document
    let form = document.getElementsByName('search')[0]
    // or, form specifically
    document.querySelector('form[name="search"]')

    // 5. The first input in that form.
    form.getElementsByTagName('input')[0]
    // or
    form.querySelector('input')

    // 6. The last input in that form
    let inputs = form.querySelectorAll('input') // find all inputs
    inputs[inputs.length-1] // take the last one
    ```


### getElement*

- We can get id of the element using the method `document.getElementById(id)`.

    ```html
    <div id="elem">
    	<p>Hello</p>
    	<div id="elem-content">World</div>
    </div>

    <script>
    document.getElementById("elem").style.background = "green";
    document.getElementById("elem-content").style.color = "white";
    </script>
    ```

- The `getElementsByTagName` method of Document interface returns an HTMLCollection of elements with the given tag name.

    ```html
    <ul id="birds">
      <li>Orange-winged parrot</li>
      <li class="endangered">Philippine eagle</li>
      <li>Great white pelican</li>
    </ul>

    <script>
    console.log(document.getElementsByTagName("li").length);
    // 3
    </script>
    ```

- `getElementsByClassName`for finding element with class name.

    ```html
    <form name="my-form">
      <div class="article">Article</div>
      <div class="long article">Long article</div>
    </form>

    <script>
    	let form = document.getElementsByName('my-form')[0];

    	let articles = form.getElementsByClassName('article').length;

    	console.log(articles);
    </script>
    ```


### querySelector*

- `document.querySelectorAll(css)` returns all elements inside matching the given CSS selector.

    ```html
    <ul>
      <li>The</li>
      <li>test</li>
    </ul>
    <ul>
      <li>has</li>
      <li>passed</li>
    </ul>
    <p>Hello World</p>
    <script>
      let elements = document.querySelectorAll('li:last-child, p');

      for (let elem of elements) {
        console.log(elem.innerHTML); // "test", "passed"
      }
    </script>
    ```

- The call to `document.querySelector(css)` returns the first element for the given CSS selector.

    ```html
    <h1>Contents</h1>

    <div class="contents">
      <ul class="book">
        <li class="chapter">Chapter 1</li>
        <li class="chapter">Chapter 1</li>
      </ul>
    </div>

    <script>
      let chapter = document.querySelector('.chapter'); // LI

      alert(chapter.closest('.book')); // UL
      alert(chapter.closest('.contents')); // DIV

      alert(chapter.closest('h1')); // null (because h1 is not an ancestor)
    </script>
    ```

- ❓ Make external links orange

    ```html
    <a name="list">the list</a>
    <ul>
      <li><a href="http://google.com">http://google.com</a></li>
      <li><a href="/tutorial">/tutorial.html</a></li>
      <li><a href="local/path">local/path</a></li>
      <li><a href="ftp://ftp.com/my.zip">ftp://ftp.com/my.zip</a></li>
      <li><a href="http://nodejs.org">http://nodejs.org</a></li>
      <li><a href="http://internal.com/test">http://internal.com/test</a></li>
    </ul>

    <script>
    	let link = document.querySelectorAll('a');
    		for ( let links of link ) {
    			if( String(links.getAttribute('href')).includes('http')) {
    			  links.style.color = 'orange';
    			};
    		}
    </script>
    ```

    ```html
    <a name="list">the list</a>
    <ul>
      <li><a href="http://google.com">http://google.com</a></li>
      <li><a href="/tutorial">/tutorial.html</a></li>
      <li><a href="local/path">local/path</a></li>
      <li><a href="ftp://ftp.com/my.zip">ftp://ftp.com/my.zip</a></li>
      <li><a href="http://nodejs.org">http://nodejs.org</a></li>
      <li><a href="http://internal.com/test">http://internal.com/test</a></li>
    </ul>

    <script>
    	let links = document.querySelectorAll('a');

    	for (let link of links) {
    	  let href = link.getAttribute('href');
    	  if (!href) continue; // no attribute

    	  if (!href.includes('://')) continue; // no protocol

    	  if (href.startsWith('http://internal.com')) continue; // internal

    	  link.style.color = 'orange';
    	}
    </script>
    ```

    ```html
    <a name="list">the list</a>
    <ul>
      <li><a href="http://google.com">http://google.com</a></li>
      <li><a href="/tutorial">/tutorial.html</a></li>
      <li><a href="local/path">local/path</a></li>
      <li><a href="ftp://ftp.com/my.zip">ftp://ftp.com/my.zip</a></li>
      <li><a href="http://nodejs.org">http://nodejs.org</a></li>
      <li><a href="http://internal.com/test">http://internal.com/test</a></li>
    </ul>

    <script>
    	let selector = 'a[href*="://"]:not([href^="http://internal.com"])';
    	let links = document.querySelectorAll(selector);

    	links.forEach(link => link.style.color = 'orange');
    </script>
    ```


## Table

- The <table> element supports (in addition to the given above) these properties.
    - An example of usage:

        ```html
        <table id="table">
          <tr>
            <td>one</td><td>two</td>
          </tr>
          <tr>
            <td>three</td><td>four</td>
          </tr>
        </table>

        <script>
          // get td with "two" (first row, second column)
          let td = table.rows[0].cells[1];
          td.style.backgroundColor = "red"; // highlight it
        </script>
        ```

    - `table.rows` – the collection of <tr> elements of the table.
    - `table.caption/tHead/tFoot` – references to elements <caption>, <thead>, <tfoot>.
    - `table.tBodies` – the collection of <tbody> elements.
    - `tr.cells` – the collection of <td> and <th> cells inside the given <tr>.
    - `tr.sectionRowIndex` – the position (index) of the given <tr> inside the enclosing <thead>/<tbody>/<tfoot>.
    - `tr.rowIndex` – the number of the <tr> in the table as a whole (including all table rows).
    - `td.cellIndex` – the number of the cell inside the enclosing <tr>.
- ❓ Select all diagonal cells

    ```html
    <!DOCTYPE HTML>
    <html>
    <head>
      <style>
        table {
          border-collapse: collapse;
        }

        td {
          border: 1px solid black;
          padding: 3px 5px;
        }
      </style>
    </head>

    <body>
      <table>
        <tr>
          <td>1:1</td>
          <td>2:1</td>
          <td>3:1</td>
          <td>4:1</td>
          <td>5:1</td>
        </tr>
        <tr>
          <td>1:2</td>
          <td>2:2</td>
          <td>3:2</td>
          <td>4:2</td>
          <td>5:2</td>
        </tr>
        <tr>
          <td>1:3</td>
          <td>2:3</td>
          <td>3:3</td>
          <td>4:3</td>
          <td>5:3</td>
        </tr>
        <tr>
          <td>1:4</td>
          <td>2:4</td>
          <td>3:4</td>
          <td>4:4</td>
          <td>5:4</td>
        </tr>
        <tr>
          <td>1:5</td>
          <td>2:5</td>
          <td>3:5</td>
          <td>4:5</td>
          <td>5:5</td>
        </tr>
      </table>
      <script>
        let table = document.body.firstElementChild;
        for(let i = 0; i < table.rows.length; i++) {
          table.rows[i].cells[i].style.background = 'red'
        }
        // your code
      </script>
    </body>
    </html>
    ```


## Methods

- `Document.createElement()` Creates a new element with the given tag name.

    ```html
    <style>
    .alert {
      padding: 15px;
      border: 1px solid #d6e9c6;
      border-radius: 4px;
      color: #3c763d;
      background-color: #dff0d8;
    }
    </style>

    <script>
      let div = document.createElement('div');
      div.className = "alert";
      div.innerHTML = "<strong>Hi there!</strong> You've read an important message.";

      document.body.append(div);
    </script>
    ```

- `Document.createTextNode()` Creates a new Text node. This method can be used to escape HTML characters.

    ```jsx
    function clicked(word) {
    	let printWord = document.createTextNode(word);
    	document.body.append(printWord);
    }

    let button = document.createElement('button');
    button.setAttribute('onclick', 'clicked("Yes ")');
    button.innerHTML = 'Click Me!'
    document.body.append(button)
    ```


# DocumentFragment

- The `DocumentFragment interface` represents a minimal document object that has no parent.

    ```jsx
    let ul = document.createElement("ul");
    document.body.append(ul);

    let fargment = new DocumentFragment();

    function getListContent() {

    	for ( let i = 1; i <= 5; i++ ) {
    		let li = document.createElement("li");
    		li.append(i);
    		fargment.append(li);
    	}

    	console.log(fargment);
    	return fargment;
    }

    ul.append(getListContent());
    ```


# Node

- Child nodes (or children) – elements that are direct children. In other words, they are nested exactly in the given one. For instance, <head> and <body> are children of <html> element.
    - `childNodes` read-only property returns a live NodeList of child nodes of the given element where the first child node is assigned index 0.

        ```html
        <html>
        <body>
          <div>Begin</div>

          <ul>
            <li>Information</li>
          </ul>

          <div>End</div>

          <script>
            for (let i = 0; i < document.body.childNodes.length; i++) {
              alert( document.body.childNodes[i] ); // Text, DIV, Text, UL, ..., SCRIPT
            }
          </script>
          ...more stuff...
        </body>
        </html>
        ```

    - `firstChild` read-only property returns the node's first child in the tree, or null if the node has no children.

        ```html
        <p id="para-01">
          <span>First span</span>
        </p>

        <script>
          var p01 = document.getElementById('para-01');
          alert(p01.firstChild.nodeName);
        </script>
        ```

    - `lastChild` read-only property returns the last child of the node.

        ```html
        var tr = document.getElementById("row1");
        var corner_td = tr.lastChild;
        ```

- Siblings are nodes that are children of the same parent.
    - The next sibling is in`nextSibling`.

        ```jsx
        alert( document.body.parentNode === document.documentElement ); // true
        ```

    - the previous one in`previousSibling`.

        ```jsx
        alert( document.head.nextSibling ); // HTMLBodyElement
        ```

    - The parent is available as `parentNode`.

        ```jsx
        alert( document.body.previousSibling ); // HTMLHeadElement
        ```

- `nodeName` to show the element name.

    ```jsx
    <p id="word">Hello World</p>
    <script>
    	let elem = document.getElementById('word');
    	console.log(elem.nodeName); // P
    </script>
    ```

- `Node.textContent` Pure text.

    ```jsx
    <div id="elem1"></div>
    <div id="elem2"></div>

    <script>
      let name = prompt("What's your name?", "<b>Winnie-the-Pooh!</b>");

      elem1.innerHTML = name; // Winnie-the-Pooh!
      elem2.textContent = name; // <b>Winnie-the-Pooh!</b>
    </script>
    ```

- ❓Count descendants

    ```html
    <!DOCTYPE HTML>
    <html>
    <body>

      <ul>
        <li>Animals
          <ul>
            <li>Mammals
              <ul>
                <li>Cows</li>
                <li>Donkeys</li>
                <li>Dogs</li>
                <li>Tigers</li>
              </ul>
            </li>
            <li>Other
              <ul>
                <li>Snakes</li>
                <li>Birds</li>
                <li>Lizards</li>
              </ul>
            </li>
          </ul>
        </li>
        <li>Fishes
          <ul>
            <li>Aquarium
              <ul>
                <li>Guppy</li>
                <li>Angelfish</li>
              </ul>
            </li>
            <li>Sea
              <ul>
                <li>Sea trout</li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>
    	<script>
    		let lists = document.getElementsByTagName('li');
    		for (let list of lists) {
    			console.log(list.textContent);
    		}
    	</script>
    </body>
    </html>
    ```

- `node.append(...nodes or strings)` – append nodes or strings at the end of node.

    ```jsx
    function clicked(word) {
    	let printWord = document.createTextNode(word);
    	document.body.append(printWord);
    }

    let button = document.createElement('button');
    button.setAttribute('onclick', 'clicked(" Yes")');
    button.innerHTML = 'Click Me!'
    document.body.append(button)
    ```

- `node.prepend(...nodes or strings)` – insert nodes or strings at the beginning of node.

    ```jsx
    function clicked(word) {
    	let printWord = document.createTextNode(word);
    	let button = document.querySelector('button');
    	button.prepend(printWord);
    }

    let button = document.createElement('button');
    button.setAttribute('onclick', 'clicked("---->")');
    button.innerHTML = 'Click Me!'
    document.body.append(button)
    ```

- `node.before()` & `node.after()`–- insert nodes or strings before & after node.

    ```html
    <ol id="ol">
      <li>0</li>
      <li>1</li>
      <li>2</li>
    </ol>

    <script>
    	ol.before("<p>");
    	ol.after("</p>");
    	console.log(document.body.outerHTML);
    	/*
    	&lt;p&gt;<ol id="ol">
      <li>0</li>
      <li>1</li>
      <li>2</li>
    	</ol>&lt;/p&gt;
      */
    </script>
    ```

- `node.replaceWith(...nodes or strings)` –- replaces node with the given nodes or strings.

    ```html
    <button onclick="clicked()">ClickMe</button>

    <p><b>Hello World</b></p>

    <script>
    	let b = document.querySelector('b');
    	function clicked() {
    		b.replaceWith("Bye World");
    	}
    </script>
    ```


# ParentNode

- ❓Show descendants in a tree.

    ```html
    <!DOCTYPE HTML>
    <html>
    <body>

      <ul>
        <li>Animals
          <ul>
            <li>Mammals
              <ul>
                <li>Cows</li>
                <li>Donkeys</li>
                <li>Dogs</li>
                <li>Tigers</li>
              </ul>
            </li>
            <li>Other
              <ul>
                <li>Snakes</li>
                <li>Birds</li>
                <li>Lizards</li>
              </ul>
            </li>
          </ul>
        </li>
        <li>Fishes
          <ul>
            <li>Aquarium
              <ul>
                <li>Guppy</li>
                <li>Angelfish</li>
              </ul>
            </li>
            <li>Sea
              <ul>
                <li>Sea trout</li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>

      <script>
    		let li = document.getElementsByTagName('li');

    		for ( let lis of li ) {
    			let lisLength = lis.getElementsByTagName('li').length;

    			if(!lisLength) continue;

    			lis.firstChild.data += `[${lisLength}]`;
    		}
    	</script>

    </body>
    </html>
    ```

- ❓ Colored clock with setInterval

    ```html
    <!DOCTYPE HTML>
    <html>
    <body>

      <div id="clock">
      <span class="hour">hh</span>:<span class="min">mm</span>:<span class="sec">ss</span>
      </div>

      <input type="button" onclick="clockStart()" value="Start">
      <input type="button" onclick="clockStop()" value="Stop">

    	<script>
    		function update() {
    	  let clock = document.getElementById('clock');
    	  let date = new Date();
    	  let hours = date.getHours();
    	  let minutes = date.getMinutes();
    	  let seconds = date.getSeconds();

    	  clock.children[0].innerHTML = hours;
    	  clock.children[1].innerHTML = minutes;
    	  clock.children[2].innerHTML = seconds;
    	}

    	let timerId;

    	function clockStart() { // run the clock
    	  if (!timerId) { // only set a new interval if the clock is not running
    	    timerId = setInterval(update, 1000);
    	  }
    	  update(); // (*)
    	}

    	function clockStop() {
    	  clearInterval(timerId);
    	  timerId = null; // (**)
    	}
    	</script>
    </body>
    </html>
    ```

- Element-only navigation:- Navigation properties listed above refer to all nodes.
    - `children` – only those children that are element nodes.

        ```html
        <html>
        <body>
          <div>Begin</div>

          <ul>
            <li>Information</li>
          </ul>

          <div>End</div>

          <script>
            for (let elem of document.body.children) {
              alert(elem); // DIV, UL, DIV, SCRIPT
            }
          </script>
          ...
        </body>
        </html>
        ```

    - `firstElementChild`, `lastElementChild` – first and last element children.

        ```jsx
        alert( document.documentElement.parentNode ); // document
        ```

    - `previousElementSibling`, `nextElementSibling` – neighbor elements.

        ```html
        <div id="div-01">Here is div-01</div>
        <div id="div-02">Here is div-02</div>
        <li>This is a list item</li>
        <li>This is another list item</li>
        <div id="div-03">Here is div-03</div>

        <script>
          let el = document.getElementById('div-03').previousElementSibling;
          document.write('<p>Siblings of div-03</p><ol>');
          while (el) {
            document.write('<li>' + el.nodeName + '</li>');
            el = el.previousElementSibling;
          }
          document.write('</ol>');
        </script>
        ```

    - `parentElement` – parent element.

        ```jsx
        console.log(document.head.parentElement);
        /*
        <html lang="en" class="working-hover">
        <head>…</head>
        <body class>…</body>
        </html>
        */
        ```



## ChildNode

- `ChildNode.remove()` method removes the object from the tree it belongs to.

    ```html
    <button onclick="clicked()">Destroy !!!</button>

    <p>Hello World</p>

    <script>
    	let button = document.querySelector('button'),
    	p = document.querySelector('p');

    	button.style.background = "red";
    	button.style.color = "white";

    	function clicked() {
    		p.remove();
    	}
    </script>
    ```

- ❓ Clear the element

    ```html
    <ol id="elem">
      <li>Hello</li>
      <li>World</li>
    </ol>

    <script>
    	function clear(ele) {
    		while (ele.firstChild) {
    			ele.childNodes[1].remove();
    		}
    	}

    	clear(document.querySelector("ol"));
    </script>
    ```

- ❓ Add a closing button

    [https://codepen.io/fillyagioro/pen/jOydryr](https://codepen.io/fillyagioro/pen/jOydryr)

- The most deeply nested element that caused the event is called a target element, accessible as `event.target`.

    [https://codepen.io/fillyagioro/pen/eYgxzBR](https://codepen.io/fillyagioro/pen/eYgxzBR)

- Stopping bubbling

    [https://codepen.io/fillyagioro/pen/eYgxzBR](https://codepen.io/fillyagioro/pen/eYgxzBR)

- ❓ Hide messages with delegation

    [https://codepen.io/fillyagioro/pen/vYgPbVe](https://codepen.io/fillyagioro/pen/vYgPbVe)


# Element

- The `matches(css)` method checks to see if the Element would be selected by the provided selectorString.

    ```html
    <ul id="birds">
      <li>Orange-winged parrot</li>
      <li class="endangered">Philippine eagle</li>
      <li>Great white pelican</li>
    </ul>

    <script>
    	let list = document.getElementsByTagName('li');
      for(let elem of list) {
        if(elem.matches('.endangered')) {
          console.log(elem.innerHTML);
        }
      }
    </script>
    ```

- The `closest()` method traverses the Element and its parents  until it finds a node that matches the provided selector string.

    ```html
    <h1>Contents</h1>

    <div class="contents">
      <ul class="book">
        <li class="chapter">Chapter 1</li>
        <li class="chapter">Chapter 1</li>
      </ul>
    </div>

    <script>
    	let chapter = document.querySelector('.chapter');
    	console.log(chapter.closest('.book').innerHTML);
    </script>
    ```

- `Element.tagName` to show the element name.

    ```jsx
    <p id="word">Hello World</p>
    <script>
    	let elem = document.getElementById('word');
    	console.log(elem.tagName); // P
    </script>
    ```

- The `innerHTML` property allows to get the HTML inside the element as a string.

    ```jsx
    <body>
      <p>A paragraph</p>
      <div>A div</div>

      <script>
        alert( document.body.innerHTML ); // read the current contents
        document.body.innerHTML = 'The new BODY!'; // replace it
      </script>

    </body>
    ```

- The `outerHTML` property contains the full HTML of the element. That’s like innerHTML plus the element itself.

    ```jsx
    <div id="elem">Hello <b>World</b></div>

    <script>
      console.log(elem.outerHTML); // <div id="elem">Hello <b>World</b></div>
    	console.log(elem.innerHTML); // Hello <b>World</b>
    </script>
    ```

- `getAttribute()` returns the elements attribute which is called.

    ```html
    <div id="elem" something-data="yes"></div>

    <script>
    	console.log(elem.getAttribute('something-data'));
    </script>
    ```

- `setAttribute()` sets the attribute value.

    ```html
    <input>

    <script>
    	let input = document.querySelector('input');
    	input.setAttribute('id', 'into')
    	console.log(input.outerHTML);
    	console.log(input.id)
    </script>
    ```

- Get attribute and there value with `attribute`.

    ```html
    <input id="hello" something="yes">

    <script>
    	let link = document.querySelector('input');

    	for ( let links of link.attributes ) {
    		console.log(links.name + ' ' + links.value);
    	}
    	// id hello
    	// something yes
    </script>
    ```

- `Element.insertAdjacent*`
    - `Element.insertAdjacentHTML()` method inserts a text as HTML, into a specified position.

        ```jsx
        let ulist = document.createElement('ul');
        document.body.append(ulist);

        let list = document.createElement('li');

        while(true) {
        	let ans = String(prompt("What you wnat inside the list?"));

        	if (!ans) {
        		break;
        	}
        	list.innerHTML = ans;
        	ulist.insertAdjacentHTML("afterBegin", `<li>${ans}</li>`);
        }
        ```

        ```jsx
        let li = document.createElement("li");
        let ul = document.querySelector("ul")
        function getListContent() {
        	for (let i = 5; i >= 1; i--) {
        	ul.insertAdjacentHTML("afterBegin", `<li>${i}</li>`);
        	}
        }

        getListContent();
        ```

    - `Element.insertAdjacentText()` – the same syntax, but a string of text is inserted “as text” instead of HTML.

        ```html
        <button onclick="clicked()">ClickMe</button>

        <p>Hello World</p>

        <script>
        	let p = document.querySelector('p');
        	function clicked() {
        		p.insertAdjacentText("beforeend", "Bye World");
        	}
        </script>
        ```

    - `Element.insertAdjacentElement()` – the same syntax, but inserts an element.

        ```html
        <button onclick="clicked()">ClickMe</button>

        <p><b>Hello World</b></p>

        <script>
        	let p = document.querySelector('p');
        	let i = document.createElement('i')
        	function clicked() {
        		p.insertAdjacentElement("afterEnd", i);
        	}
        	i.innerHTML = "Bye World";
        </script>
        ```

    - `"beforebegin"` – insert `html` immediately before `elem`,
    - `"afterbegin"` – insert `html` into `elem`, at the beginning,
    - `"beforeend"` – insert `html` into `elem`, at the end,
    - `"afterend"` – insert `html` immediately after `elem`.
- ❓ Insert the HTML in the list

    ```html
    <ul id="ul">
      <li id="one">1</li>
      <li id="two">4</li>
    </ul>

    <script>
    	one.insertAdjacentHTML("afterend", "<li>2</li><li>3</li>");
    </script>
    ```

- The `className` property of the Element interface gets and sets the value of the class attribute of the specified element.

    ```jsx
    let div = document.createElement('div');
    div.className = "hello";
    div.innerHTML = div.className;

    document.body.append(div);
    ```

- Window sizes
    - `clientWidth` / `clientHeight` Width/height of the window.

        ```jsx
        console.log(document.documentElement.clientWidth);
        console.log(document.documentElement.clientHeight);
        ```

    - `document.documentElement.scrollWidth/scrollHeight` Width/height of the document.
- If there are no paddings, then `clientWidth/Height` is exactly the content area, inside the borders and the scrollbar (if any).

    ```jsx
    let h1 = document.body.querySelector('h1');
    h1.clientHeight;
    ```

- `Element.scrollIntoView()`scroll into the view of line.

    ```jsx
    let h1 = document.body.querySelector('h1');

    h1.scrollIntoView()
    ```

- `Element.getBoundingClientRect()` returns information about left, top, right, bottom, x, y, width, and height.
- `onmouseover` change element when you hover over element & `onmouseout` change element when hover out over element.

    [https://codepen.io/fillyagioro/pen/RwKzzxg](https://codepen.io/fillyagioro/pen/RwKzzxg)

- `onmousedown` change element when you click over element & `onmouseup` change element when click done.

    [https://codepen.io/fillyagioro/pen/JjEQgRJ](https://codepen.io/fillyagioro/pen/JjEQgRJ)

- ❓ Catch links in the element

    [https://codepen.io/fillyagioro/pen/PoWrMeg](https://codepen.io/fillyagioro/pen/PoWrMeg)


# Event

- The `preventDefault()` method cancels the event if it is cancelable, meaning that the default action that belongs to the event will not occur.

    [https://codepen.io/fillyagioro/pen/GRrbVBe](https://codepen.io/fillyagioro/pen/GRrbVBe)


# EventTarget

- The `addEventListener()` method attaches an event handler to the specified element.

    ```html
    <table id="outside">
      <tr><td id="t1">one</td></tr>
      <tr><td id="t2">two</td></tr>
    </table>
    <script>
    	let elem = document.querySelector('table');

    	function change() {
    		let td = document.getElementsByTagName('td');
    		if (td[1].innerHTML == "two") {
    			td[1].innerHTML = "three";
    		} else {
    			td[1].innerHTML = "two"
    		}
    	}

    	elem.addEventListener('click', change, false)
    </script>
    ```


# Window

- The method `scrollBy(x,y)` scrolls the page relative to its current position. For instance, scrollBy(0,10) scrolls the page 10px down.

    ```jsx
    window.scrollBy(0,10)
    ```

- `Window.scrollTo()` scrolls to a particular set of coordinates in the document.

    ```jsx
    window.scrollTo()
    ```


# CSSStyleDeclaration.cssText

- The `cssText` property of the CSSStyleDeclaration interface returns or sets the text of the element's inline style declaration only.

    ```jsx
    let message = document.createElement('div');

    message.style.cssText = "background: red; color: white";

    message.innerHTML = "Hello, World";

    document.body.append(message);
    ```


# HTMLElement

- Hide the element with `HTMLElement.hidden`.

    ```jsx
    <div id="elem">Hello <b>World</b></div>
    <script>
    	let bold = elem.getElementsByTagName('b')[0];
    	setInterval(() => bold.hidden = !bold.hidden, 500);
    </script>
    ```

- ❓ Hide on click

    ```html
    <!DOCTYPE HTML>
    <html>

    <head>
      <meta charset="utf-8">
    </head>

    <body>

      <input type="button" id="hider" value="Click to hide the text" />

      <div id="text">Text</div>

      <script>
        hider.onclick = () => {
          let text = document.getElementById('text');
          text.hidden = true;
        }
      </script>

    </body>
    </html>
    ```

- The style attribute is a string, but the style property is an object.

    ```html
    <div id="div" style="color:red;font-size:120%,al">Hello</div>

    <script>
    	console.log(div.style.color);
    	// red
    	div.style.background = "green";

    	console.log(div.style);
    	// empty
    </script>
    ```

- The `HTMLElement.offsetWidth/Height` read-only property returns the layout width of an element as an integer.

    ```jsx
    h1 = document.body.querySelector('h1');
    // h1.offsetHeight
    ```


# HTMLInputElement

- DOM elements also have additional properties, in particular those that depend on the class.

    ```jsx
    <input type="text" id="elem" value="value">

    <script>
    	let elem = document.getElementById('elem');
    	console.log(elem.value);
    	console.log(elem.type);
    </script>
    ```

- Accessing the element: this

    ```html
    <button onclick="alert(this.innerHTML)">Click me</button>
    ```


# HTMLOrForeignElement

- Non-standard attributes are used to pass custom data from HTML to JavaScript, or to “mark” HTML-elements for JavaScript.

    ```html
    <!-- mark the div to show "name" here -->
    <div show-info="name"></div>
    <!-- and age here -->
    <div show-info="age"></div>

    <script>
    	let user = {
    		name: "Pete",
    		age: 25
    	};

    	 for(let div of document.querySelectorAll('[show-info]')) {
    	 	let text = div.getAttribute('show-info');
    		div.innerHTML = user[text];
    	}
    </script>

    ```

- All attributes starting with “data-” are reserved for programmers’ use. They are available in the dataset property.

    ```html
    <style>
      .order[data-order-state="new"] {
        color: green;
      }

      .order[data-order-state="pending"] {
        color: blue;
      }

      .order[data-order-state="canceled"] {
        color: red;
      }
    </style>

    <div id="order" class="order" data-order-state="new">
      A new order.
    </div>

    <script>
    	order.dataset.orderState = 'padding';

    	console.log(order.outerHTML);
    	// <div id="order" class="order" data-order-state="padding">A new order.</div>
    </script>
    ```


# GlobalEventHandlers.onclick

- The `onclick` event occurs when the user clicks on an element.

    ```html
    <button>Click Me</button>

    <script>
      let button = document.querySelector('button');

      button.onclick = () => alert("Hello World")
    </script>
    ```


# Location

- `location` interface represents the location (URL) of the object it is linked to.
    - `location.href` shows URL.

        ```jsx
        alert(location.href); // shows current URL
        if (confirm("Go to Wikipedia?")) {
          location.href = "https://wikipedia.org"; // redirect the browser to another URL
        }
        ```



# Web Console Helpers

- `$0` The currently-inspected element in the page. `$0.style.background = 'red'`
