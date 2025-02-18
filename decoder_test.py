import json

import torch
import numpy as np

try:
    from build.wrapper import KWSDecoder
except ImportError:
    from wrapper import KWSDecoder
from beam_search import prefix_beam_search

print("###################")
print("# ENGLISH example #")
print("###################")

with open('resources/labels.json') as f:
    labels = json.load(f)

data = torch.load('resources/output.pth')
data = data.squeeze().numpy()

keywords = ['think', 'sport', 'cheat', 'kids', 'remember']
keywords = [word.upper() for word in keywords]

ref_result = prefix_beam_search(labels, 0, data, keywords)
print('ref_result:')
for key in ref_result.keys():
    print(f'key: {key}')
    for keyword in ref_result[key]:
        print(f'\t{keyword}')

print('c++_result:')
decoder = KWSDecoder(labels, 0)
decoder.add_words(keywords)
result = decoder.search(data)
print(json.dumps(result, indent=4))

print("\n" * 3)
print("###################")
print("# PERSIAN example #")
print("###################")
with open('resources/fa_labels.json') as f:
    fa_labels = json.load(f)

fa_data = torch.load('resources/fa_output.pth')
fa_data = fa_data.squeeze().numpy()

fa_keywords = ["پادشاه", "پرگار", "ارادت", "جلال", "عظمت", "طالبی"]

ref_result = prefix_beam_search(fa_labels, 0, fa_data, fa_keywords)
print('ref_result:')
for key in ref_result.keys():
    print(f'key: {key}')
    for keyword in ref_result[key]:
        print(f'\t{keyword}')

print('c++_result:')
decoder = KWSDecoder(fa_labels, 0)
decoder.add_words(fa_keywords)
result = decoder.search(fa_data)
print(json.dumps(result, indent=4, ensure_ascii=False))
