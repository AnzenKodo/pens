#!/usr/bin/env -S deno run --ext=js -A

const path =
  `${Deno.env.get("HOME")}/.config/BraveSoftware/Brave-Browser/Default/`;
const extPath = path + "Extensions/";

const files = Deno.readDirSync(path + "Extensions/");

const data = [...files].map((val) => {
  const dir = Deno.readDirSync(extPath + val.name);

  const dirVersionName = [...dir][0].name;

  const dirVersionPath =
    `${extPath}${val.name}/${dirVersionName}/manifest.json`;
  const dirVersion = Deno.readTextFileSync(dirVersionPath);

  const map = new Map(Object.entries(JSON.parse(dirVersion)));

  const mapFormat = new Map();
  mapFormat.set("id", val.name);
  mapFormat.set("name", map.get("name"));
  mapFormat.set("description", map.get("description"));
  mapFormat.set("homepage_url", map.get("homepage_url"));
  mapFormat.set(
    "chrome_webstore_url",
    "https://chrome.google.com/webstore/detail/" + val.name,
  );

  return mapFormat;
});

const obj = new Object();
obj.data = data.map((val) => Object.fromEntries(val));

Deno.writeTextFile(
  Deno.env.get("DOTFILES") + "/data/extensions.json",
  JSON.stringify(obj.data, null, 2)
  );
