from cs50 import get_string
import re


def cmpt_letter(text):
    n = 0
    for i in text:
        if i.isalpha():
            n += 1
    return n


def cmpt_word(text):
    word_list = text.split()    # 默认空格分隔句子为列表
    # print(word_list)
    return len(word_list)


def cmpt_sentence(text):
    sentence_list = re.split(r'[.\!?]', text)   # 以. ! ? 分割文本
    # print(sentence_list)
    return len(sentence_list) - 1               # 减去最后一个标点分割为俩


def cmpt_index(text):
    letters = cmpt_letter(text)
    words = cmpt_word(text)
    sentence = cmpt_sentence(text)

    # print("letters: {0}, words: {1}, sentence: {2}".format(letters, words, sentence))

    L = letters / (words / 100)
    S = sentence / (words / 100)

    # print("L: {0}, S: {1}".format(L, S))

    return 0.0588 * L - 0.296 * S - 15.8


def main():
    while True:
        text = get_string("Text: ")
        break

    index = round(cmpt_index(text))

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade {0}".format(index))


if __name__ == "__main__":
    main()
