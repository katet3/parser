#pragma once

/* Проверка на то включен ли этот файл в другие */
#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

/* Класс синтаксический анализатор
* 
*/
class SyntaxAnalyzer {
private:
    /* Входной файл  - файл указатель на файл с которого считывается информация
    *  Выходной файл - файл куда записывается результат
    *  translation_map - карта отображений лексем
    */
    std::unique_ptr<std::ifstream> file_input_;
    std::unique_ptr<std::ofstream> file_output_;
    std::unordered_map<std::string, std::string> translation_map_;

public:
    /* Конструкторы */
    SyntaxAnalyzer(const std::string& input_file_path, const std::string& output_file_path);
    
    /* Методы */
    void analyze_and_translate();

    /* Getters и Setters */
    const std::unordered_map<std::string, std::string>& get_translation_map() const;
    void set_translation_map(const std::unordered_map<std::string, std::string>& translation_map);

    /* Перегрузки */
    friend std::ostream& operator<<(std::ostream& os, SyntaxAnalyzer& obj);

private:
    /* Переводчик, написано блять уже */
    std::string translate_words(const std::string& code);
};

#endif  // SYNTAX_ANALYZER_H_