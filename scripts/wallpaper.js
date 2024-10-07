#!/usr/bin/env -S deno run --ext=js -A

import { download } from "https://deno.land/x/download@v1.0.1/mod.ts";
import {
  DOMParser,
} from "https://deno.land/x/deno_dom@v0.1.38/deno-dom-wasm.ts";
import $ from "https://deno.land/x/dax/mod.ts";

const query = (num) => {
  return `#mweb-unauth-container > div > div > div:nth-child(5) > div > div.F6l.k1A.zI7.iyn.Hsu > div > div:nth-child(1) > div > div > div.Pj7.sLG.XiG.ho-.m1e > div > div:nth-child(${num}) > div > div.XiG.zI7.iyn.Hsu > img`;
};

const getImg = async (query) => {
  const url = `https://www.pinterest.com/AnzenKodo/imgs/`;
  const html = await fetch(url).then((res) => res.text());
  const doc = new DOMParser().parseFromString(html, "text/html");
  const imgUrl = doc?.querySelector(query)?.getAttribute("src");

  return imgUrl?.replace(
    "https://i.pinimg.com/200x",
    "https://i.pinimg.com/originals",
  );
};

const saveData = async (url, name) => {
  const filename = Deno.env.get("DOTFILES") + "/data/desktop.json";
  const data = JSON.parse(Deno.readTextFileSync(filename));

  await $`feh --bg-scale $XDG_PICTURES_DIR/Wallpaper.png`;

  if (data[name] === url) return console.log("Wallpaper already saved!");
  if (name === "wallpaper") {
    await $`import -window root $DOTFILES/screenshot.jpg`;
  }

  data[name] = url;
  Deno.writeTextFileSync(filename, JSON.stringify(data, null, 2));
};

const saveImg = async (num, path) => {
  const url = await getImg(query(num));
  await download(url, {
    file: "Wallpaper.png",
    dir: path,
  });
  console.log(`Downloaded new Wallpaper ${num}!`);
  saveData(url, num === 1 ? "wallpaper" : "browser_wallpaper");
};

saveImg(1, Deno.env.get("XDG_PICTURES_DIR"));

saveImg(
  2,
  Deno.env.get("HOME") +
    "/.config/BraveSoftware/Brave-Browser/Default/sanitized_background_images",
);

