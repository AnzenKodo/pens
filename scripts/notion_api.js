const apiKey = Deno.env.get("NOTION_API_KEY");
console.log(apiKey);

const data = await fetch(
  "https://api.notion.com/v1/databases/c2dc30d7174b437188c91ef663bc99d2",
  {
    method: "GET",
    headers: {
      "Authorization": `Bearer ${apiKey}`,
      "Content-Type": "application/json",
      "Notion-Version": "2022-06-28",
    },
  },
).then((res) => res.json());

console.log(data.description[0].plain_text);
