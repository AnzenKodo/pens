from flask import Flask, request
import urllib.parse
import requests

def index():
    return """
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>Summarizer</title>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width" />
    <link
      rel="icon"
      href="https://iconmonstr.com/wp-content/g/gd/makefg.php?i=../releases/preview/7.8.0/png/iconmonstr-cut-filled.png&r=156&g=166&b=165"
    />
    <style>
      :root {
        color-scheme: dark;
      }
      body {
        max-width: 30rem;
        margin: 0 auto;
        padding: 1em 1em;
        text-align: center;
        font-family: system-ui;
      }
      .textarea {
        display: block;
        padding: 3%;
        overflow: hidden;
        resize: vertical;
        min-height: 100px;
        max-width: 100%;
        border: 1px solid;
        border-radius: 10px;
      }
      .textarea[contenteditable]:empty::before {
        content: 'Enter words in Summarizer';
        color: gray;
      }
      .width label {
        display: inline;
      }
      input[type='submit'] {
        min-width: 120px;
        height: 35px;
        font-weight: bold;
        cursor: pointer;
        transition: all 0.3s ease;
        position: relative;
        border-radius: 5px;
        border: none;
        background: #343a40;
        box-shadow: 0 5px #212529;
      }
      input[type='submit']:hover {
        box-shadow: 0 3px #212529;
        top: 1px;
      }
      input[type='submit']:active {
        box-shadow: 0 0 #212529;
        top: 5px;
      }
      .no-center {
        text-align: left;
      }
      .output {
        margin-top: 3em;
        background: black;
        padding: 0.1em 1em;
        border-radius: 10px;
      }
      .output-text {
        font-size: 1.1em;
      }
      .output-text:after {
        content: '|';
      }
    </style>
    <script type="module">
      const type = (text) => {
        const output = document.querySelector('.output-text code');
        output.innerHTML = "";
        let i = 0;
        const add = () => {
          output.innerHTML += text[i++];
          if (text[i] === undefined) clearInterval(timeout);
        };
        const timeout = setInterval(add, 50);
      };

      const getPrompt = async (text, width) => {
        const res = await fetch(
          `http://127.0.0.1:5000/api?prompt=${text}&width=${width}`
        );
        return res.text();
      };

      const form = document.querySelector('form');
      form.addEventListener('submit', (event) => {
        event.preventDefault();
      });
      form.addEventListener('submit', async () => {
        const text = document.querySelector('.textarea');
        const width = document.querySelector('.width input');
        const prompt = await getPrompt(text.textContent, width.value);
        type(prompt);
      });

     </script>
  </head>
  <body>
    <main>
      <h1>Summarizer</h1>
      <form>
        <p class="textarea no-center" role="textbox" contenteditable></p>
        <p class="width">
          <label name="width">Width:</label>
          <input type="number" name="width" value="100" />
        </p>
        <input type="submit" />
      </form>
      <div class="no-center output">
        <h2>Summarized Text:</h2>
        <p class="output-text">
          <code></code>
        </p>
      </div>
    </main>
  </body>
</html>
"""

def query(input, output_length):
  api_url = "https://api-inference.huggingface.co/models/facebook/bart-large-cnn" #@param {type: "string"}
  auth_token = "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" #@param {type:"string"}

  response = requests.post(
      api_url, 
      headers={"Authorization": f"Bearer {auth_token}"}, 
      json={
        "inputs": input,
        "parameters": {
          "do_sample": False, 
          "max_length": output_length, 
          "min_length": output_length
        },
      }
  )
  
  return response.json()[0]['summary_text']

app = Flask(__name__)

@app.route('/')
def root():
  return index()

@app.route('/api')
def api():
  prompt = urllib.parse.unquote(request.args.get('prompt'))
  width = int(request.args.get('width'))
  return query(prompt, width)

if __name__ == '__main__':
  app.run()
