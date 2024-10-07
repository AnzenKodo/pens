# !/bin/bash

# Checks the markdown install or not

if ! [ -x "$(command -v markdown)" ]; then
	tput setaf 1
	echo "Error: markdown is not installed"
	tput sgr0
	echo "Install it by entering this command:"
	echo "\nsudo apt install markdown\n"
	exit
fi

# Variable

name="Filly Agioro"
website="https://fillyagioro.vercel.app"
blog="https://fillyblog.vercel.app"

# The main functions

head() {
	cat <<-_EOF_
		<title>$name Blog</title>

		<meta name="description" content="This is my personal website which shows information about me.">
		<meta name="theme-color" content="#00eab5z">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta name="msapplication-TileColor" content="#2b5797">

		<link rel="apple-touch-icon" sizes="180x180" href="/dist/logo/apple-touch-icon.png" />
		<link rel="icon" type="image/png" sizes="32x32" href="/dist/logo/favicon-32x32.png" />
		<link rel="icon" type="image/png" sizes="16x16" href="/dist/logo/favicon-16x16.png" />
		<link rel="manifest" href="manifest.json" />
		<link rel="preload" href="/dist/style.css" as="style">
		<link rel="stylesheet" href="/dist/style.min.css">
	_EOF_
	return
}

footer() {
	cat <<-_EOF_
		</article>
		<footer>
		<p><a href="/rss.xml">RSS</a> | @<a href="$website">Filly Agioro</a> under <a href="/LICENSE.txt">GPL 3.0</a> | <a href="https://github.com/FillyAgioro/script-blog">Website Source</a></p>
		</footer>
		</section>
	_EOF_
	return
}

# index.html functions

index() {

	cat <<-_EOF_
		<section class="center">
		<main>
		<p class="title">$name Blog</p>
		</main>
		<article class="content">
	_EOF_

	# Main compontent of index.html
	for i in posts/*.md; do
		title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.' | cut -b 7- | sed '/^leaf/ s/-/_/' | tr '-' ' ')
		file_title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.')
		cat <<-_EOF_
			<p><a href="/dist/$file_title.html">$title</a></p>
		_EOF_
	done
	return
}

index_main() {
	cat <<-_EOF_
		<html lang="en">
		<head>
			$(head)
		<head>
		<body>
			$(index)
		   $(footer)
		</body>
		</html>
	_EOF_
}
echo $(index_main) >index.html

# Posts functions

for i in posts/*.md; do

	title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.' | cut -b 7- | tr '-' ' ')
	file_title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.')
	date=$(date -I -r $i)

	posts_main() {
		cat <<-_EOF_
			<html lang="en">
			<head>
			$(head)
			<head>
			<body>

			<section class="center">
			<main>
			<p class="title"><a href="/">$name Blog</a></p>
			<p class="title">$title</p>
			<p>Published or Updated on <time>$date</time></p>
			</main>
			<article class="content">

			$(markdown $i)

			$(footer)
			</body>
			</html>
		_EOF_
		return
	}

	echo $(posts_main) >dist/$file_title.html
done

# RSS functions

rss() {

	cat <<-_EOF_
		<?xml version="1.0" encoding="UTF-8" ?>
		<rss version="2.0">
		<channel>
		<link>$blog</link>
		<description>My is my Blog where I write about my own world.</description>
		<language>en-us</language>
		<copyright>@$name under GPL 3.0</copyright>
		<author>$name</author>
		<managingEditor>fillyagioro.perpetuana@slmail.me</managingEditor>
		<lastBuildDate>$(date)</lastBuildDate>
	_EOF_

	for i in posts/*.md; do

		title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.' | cut -b 7- | tr '-' ' ')
		file_title=$(printf '%s\n' "${i%}" | cut -f 1 -d '.')
		date=$(date -I -r $i)

		cat <<-_EOF_
			<item>
			<title>$title</title>
			<link>$blog/$file_title</link>
			<pubDate>$date</pubDate>
			</item>
		_EOF_
	done

	cat <<-_EOF_
		</channel>
		</rss>
	_EOF_

	return
}

echo "$(rss)">rss.xml
