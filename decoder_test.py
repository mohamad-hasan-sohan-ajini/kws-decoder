import json

import torch
import numpy as np

try:
    from build.wrapper import KWSDecoder
except ImportError:
    from wrapper import KWSDecoder
from beam_search import prefix_beam_search

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
print(result)
