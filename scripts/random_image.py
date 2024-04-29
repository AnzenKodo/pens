import requests
import sys

try:
  keyword=sys.argv[1]
except:
  keyword="random"

try:
  size=sys.argv[2]
except:
  size="500x500"

r = requests.get(f"https://source.unsplash.com/{size}/?{keyword}")
with open('./image.jpeg', 'wb') as f:
  f.write(r.content)
