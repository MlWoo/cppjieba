#ifndef CPPJIEAB_JIEBA_H
#define CPPJIEAB_JIEBA_H

#include "QuerySegment.hpp"
#include "KeywordExtractor.hpp"

namespace cppjieba {

class Jieba {
 public:
  Jieba(const string& dict_path, 
        const string& model_path,
        const string& user_dict_path, 
        const string& idfPath, 
        const string& stopWordPath); 
  ~Jieba();

  struct LocWord {
    string word;
    size_t begin;
    size_t end;
  }; // struct LocWord

  void Cut(const string& sentence, vector<string>& words, bool hmm = true) const;
  void Cut(const string& sentence, vector<Word>& words, bool hmm = true) const;
  void CutAll(const string& sentence, vector<string>& words) const;
  void CutAll(const string& sentence, vector<Word>& words) const;
  void CutForSearch(const string& sentence, vector<string>& words, bool hmm = true) const;
  void CutForSearch(const string& sentence, vector<Word>& words, bool hmm = true) const;
  void CutHMM(const string& sentence, vector<string>& words) const;
  void CutHMM(const string& sentence, vector<Word>& words) const;
  void CutSmall(const string& sentence, vector<string>& words, size_t max_word_len) const;
  void CutSmall(const string& sentence, vector<Word>& words, size_t max_word_len) const;
  
  void Tag(const string& sentence, vector<pair<string, string> >& words) const;
  string LookupTag(const string &str) const;
  bool InsertUserWord(const string& word, const string& tag = UNKNOWN_TAG);

  bool InsertUserWord(const string& word,int freq, const string& tag = UNKNOWN_TAG);

  bool Find(const string& word);

  void ResetSeparators(const string& s);

  const DictTrie* GetDictTrie() const;
  
  const HMMModel* GetHMMModel() const;

  void LoadUserDict(const vector<string>& buf);

  void LoadUserDict(const set<string>& buf);

  void LoadUserDict(const string& path);

 private:
  DictTrie dict_trie_;
  HMMModel model_;
  
  // They share the same dict trie and model
  MPSegment mp_seg_;
  HMMSegment hmm_seg_;
  MixSegment mix_seg_;
  FullSegment full_seg_;
  QuerySegment query_seg_;

 public:
  KeywordExtractor extractor;
}; // class Jieba

} // namespace cppjieba

#endif // CPPJIEAB_JIEBA_H
