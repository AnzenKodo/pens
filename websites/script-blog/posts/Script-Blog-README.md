# Script Blog

This simple easy to modify shell script site generator which helps you to write blog. This theme is without any kind of JavaScript or any other kind of programming language. This theme only contain HTML, Shell, SCSS, and SCSS files. Easy to understand code and noob friendly. You only have to edit [`scriptblog.sh`](/scriptblog.sh) file and make markdown file in [`posts`](/posts) folder.

## 📕 Prerequisites

You have to install the `markdown` cli program in order to run the script.

```bash
sudo apt install markdown # Ubuntu and Debian
```

## 🔨 Running

- Clone the repo

```bash
git clone https://github.com/FillyAgioro/script-blog.git
```

- Go repo

```bash
cd script-blog
```

- Make script executable

```bash
chmod a+x ./scriptblog.sh
```

- Run the script

```bash
./scriptblog.sh
```

## 📁 Editing the theme

You only have to edit [`scriptblog.sh`](/scriptblog.sh) file. But if you want to customize it more then edit [`style.scss`](style.scss) file.

### Change the title and link of the website

If you want to change the title and link in the website then edit following code in [`scriptblog.sh`](/scriptblog.sh).

```bash
name="Filly Agioro"
website="https://fillyagioro.vercel.app"
blog="https://fillyblog.vercel.app"
```

### 💄 Change the color of website

If you want to change the color of the website then edit following code in [`style.scss`](/style.scss).

```scss
$brand-color: #00eab5;
$bg-color: black;
$font-color: white;
```

### ⬆️ To edit in advance level

If you want to edit it more then you have to know how write shell script and you have to know SASS or CSS.

### ❌ Don't want learn SASS

If you only know css then css file is in [`style.css`](dist/style.css). Also you have to edit color individually.

**Note**: Remember I have link [`style.min.css`](dist/style.min.css) in HTML files you should also edit that. 

## ✏️ How to write posts

You only have to make file in [`posts`](posts) with `.md`. And write post in [markdown](https://www.markdownguide.org/).

### 🖼️ Add photos

Add you photos in [`photos`](photos) folder. Like following code:

```md
![Shell-Script](/posts/Shell-Script.md)
```

## 🚸 Support

To support this project development please consider [DONATING](https://fillyagioro.vercel.app/#support).

## 👥 Contributing

Please read [`CONTRIBUTING`](https://github.com/FillyAgioro/.github/blob/main/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## ✏️ Authors

See also the list of [contributors](@all) who participated in this project.

## 📄️ License

This project is licensed under the MIT License - see the [`LICENSE`](/LICENSE.txt) file for details