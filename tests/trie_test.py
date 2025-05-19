from wrapper import Trie

trie = Trie()
trie.add_word('مادرید')

print(trie.has_word('مادرید'))
print(trie.has_word('مادر'))
print(trie.is_promising('مادر'))
print(trie.is_promising('مار'))
