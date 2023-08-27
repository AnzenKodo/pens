#!/usr/bin/env -S deno run --ext=js -A

import dree from "https://esm.sh/dree@3.3.8";

async function repo() {
  return await fetch(
    "https://api.github.com/repos/AnzenKodo/dotfiles",
  )
    .then((res) => res.json())
    .then((res) => {
      const { name, description } = res;
      return { name, description };
    });
}

function ext() {
  const ext = Deno.readTextFileSync("data/extensions.json");
  const maps = new Map(Object.entries(JSON.parse(ext)));

  let links = "\n";
  for (const [_key, value] of maps) {
    if (value.name.match(/^__MSG_/)) continue;
    if (value.description?.match(/^__MSG_/)) delete value.description;

    if (value.homepage_url) {
      if (value.description) {
        links +=
          `- [${value.name}](${value.homepage_url}) - ${value.description}\n`;
      } else {
        links += `- [${value.name}](${value.homepage_url})\n`;
      }
    } else {
      if (value.description) {
        links +=
          `- [${value.name}](${value.chrome_webstore_url}) - ${value.description}\n`;
      } else {
        links += `- [${value.name}](${value.chrome_webstore_url})\n`;
      }
    }
  }

  return links;
}

function tree() {
  const treeJson = dree.scan("./", {
    exclude: /\.git|\.github|__pycache__|__init__.py|.md|readme.js/,
  });
  return dree.parseTree(treeJson);
}

async function bm() {
  const json = await Deno.readTextFile("./data/bookmarks.json")
    .then((res) => JSON.parse(res));

  const obj = json.roots.bookmark_bar.children;
  const bookmarks = obj.filter((val) => val.id === "1035");
  const child = bookmarks[0].children;

  let md = "";
  function loopNested(objs, count = 2) {
    const preCount = count;

    for (const obj of objs) {
      if (obj.type === "folder") {
        md += `\n${"#".repeat(preCount)} ${obj.name}\n`;

        loopNested(obj.children, ++count);
      } else {
        const title = obj.name.match(/^.*(?=\s-\s)/);
        const des = obj.name.replace(/^.*\s-\s/, "");

        if (title) {
          md += `- [${title[0]}](${obj.url}) - ${des}\n`;
        } else {
          md += `- [${obj.name}](${obj.url})\n`;
        }
      }
      count = preCount;
    }

    return md;
  }

  return loopNested(child);
}

function replace(content, value) {
  const name = Object.keys(value)[0];
  const rName = name.toUpperCase();
  const regex = new RegExp(
    `(?<=<!--${rName}:START-->)([\n]|.)*(?=<!--${rName}:END-->)`,
  );
  return content.replace(regex, value[name]);
}

const filePath = "./README.md";
let readme = Deno.readTextFileSync(filePath);

const repoInfo = await repo();
const title = `AK#${
  repoInfo.name.charAt(0).toUpperCase() + repoInfo.name.slice(1)
}`;
const description = "\n" + repoInfo.description + "\n";
readme = replace(readme, { title });
readme = replace(readme, { description });

const extensions = ext();
readme = replace(readme, { extensions });

const tRee = tree();
readme = replace(readme, { tRee });

const bookmarks = await bm();
readme = replace(readme, { bookmarks });

Deno.writeTextFileSync(filePath, readme);
