import requests
from lxml import html
import json

etree = html.etree
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36'
}
def hupu(url):
    page_text = requests.get(url, headers=headers).text
    # print(page_text)
    tree = etree.HTML(page_text)
    li_list = tree.xpath('//*[@id="container"]/div/div[2]/div/div[2]/div[3]/ul')
    # 初始一个字典
    content = {}
    for li in li_list:
        content = li.xpath('li/div/div[1]/a/text()')
        href = li.xpath('li/div/div[1]/a/@href')
    return content,href

content, href = hupu('https://bbs.hupu.com/liaoning')
#把content href 存到一个字典中{"content":content,"href":href}"}
x = {}
for i in range(len(content)):
    x[content[i]] = "https://bbs.hupu.com" + href[i]

print(json.dumps(x, ensure_ascii=False))