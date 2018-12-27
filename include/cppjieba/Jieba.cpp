#include "Jieba.hpp"

using namespace cppjieba;
Jieba::Jieba(const string& dict_path, 
        const string& model_path,
        const string& user_dict_path, 
        const string& idfPath, 
        const string& stopWordPath) 
    : dict_trie_(dict_path, user_dict_path),
      model_(model_path),
      mp_seg_(&dict_trie_),
      hmm_seg_(&model_),
      mix_seg_(&dict_trie_, &model_),
      full_seg_(&dict_trie_),
      query_seg_(&dict_trie_, &model_),
      extractor(&dict_trie_, &model_, idfPath, stopWordPath) {
}
Jieba:: ~Jieba() {
}

void Jieba::Cut(const string& sentence, vector<string>& words, bool hmm) const {
  mix_seg_.Cut(sentence, words, hmm);
}
void Jieba::Cut(const string& sentence, vector<Word>& words, bool hmm) const {
  mix_seg_.Cut(sentence, words, hmm);
}
void Jieba::CutAll(const string& sentence, vector<string>& words) const {
  full_seg_.Cut(sentence, words);
}
void Jieba::CutAll(const string& sentence, vector<Word>& words) const {
  full_seg_.Cut(sentence, words);
}
void Jieba::CutForSearch(const string& sentence, vector<string>& words, bool hmm) const {
  query_seg_.Cut(sentence, words, hmm);
}
void Jieba::CutForSearch(const string& sentence, vector<Word>& words, bool hmm) const {
  query_seg_.Cut(sentence, words, hmm);
}
void Jieba::CutHMM(const string& sentence, vector<string>& words) const {
  hmm_seg_.Cut(sentence, words);
}
void Jieba::CutHMM(const string& sentence, vector<Word>& words) const {
  hmm_seg_.Cut(sentence, words);
}
void Jieba::CutSmall(const string& sentence, vector<string>& words, size_t max_word_len) const {
  mp_seg_.Cut(sentence, words, max_word_len);
}
void Jieba::CutSmall(const string& sentence, vector<Word>& words, size_t max_word_len) const {
  mp_seg_.Cut(sentence, words, max_word_len);
}

void Jieba::Tag(const string& sentence, vector<pair<string, string> >& words) const {
  mix_seg_.Tag(sentence, words);
}
string Jieba::LookupTag(const string &str) const {
  return mix_seg_.LookupTag(str);
}
bool Jieba::InsertUserWord(const string& word, const string& tag) {
  return dict_trie_.InsertUserWord(word, tag);
}

bool Jieba::InsertUserWord(const string& word,int freq, const string& tag) {
  return dict_trie_.InsertUserWord(word,freq, tag);
}

bool Jieba::Find(const string& word)
{
  return dict_trie_.Find(word);
}

void Jieba::ResetSeparators(const string& s) {
  //TODO
  mp_seg_.ResetSeparators(s);
  hmm_seg_.ResetSeparators(s);
  mix_seg_.ResetSeparators(s);
  full_seg_.ResetSeparators(s);
  query_seg_.ResetSeparators(s);
}

const DictTrie* Jieba::GetDictTrie() const {
  return &dict_trie_;
} 

const HMMModel* Jieba::GetHMMModel() const {
  return &model_;
}

void Jieba::LoadUserDict(const vector<string>& buf)  {
  dict_trie_.LoadUserDict(buf);
}

void Jieba::LoadUserDict(const set<string>& buf)  {
  dict_trie_.LoadUserDict(buf);
}

void Jieba::LoadUserDict(const string& path)  {
  dict_trie_.LoadUserDict(path);
}

