import { Parser } from "npm:@json2csv/plainjs";

const data = {
  "name": "jone",
  "roll": 23,
};

const parser = new Parser();
Deno.writeTextFile(
  "data.csv",
  parser.parse(data),
);
