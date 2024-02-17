from pathlib import Path
import os
from twitter.account import Account

path = f"{Path.home()}/Documents/Notes/XPosts/Text.md"
fileread = open(path, "r")
file = fileread.readlines()

# account = Account(cookies={
    # "ct0": file[0].split("=")[1],
    # "auth_token": file[1].split("=")[1]
# })

new_lines = []
count = -1
lines_count = 0
post = []
imgs = ""
start = False
for line in file:
    count += 1

    if line == "```\n":
        if start:
            lines_count += 1
            start = False
            print(lines_count)
        else:
            start = True
        continue

    if start:
        if len(post) == lines_count:
            post.append({"text": line})
        else:
            post[lines_count]["text"] += line
        # pass

if imgs == "":
    # account.tweet(post)
    print(post)
else:
    print(imgs.split(","))
print(new_lines)
fileread.close()
