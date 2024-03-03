#include "syntax_analyzer.h"

using std::cout;
using std::cin;
using std::endl;


/* Конструктор по двум файлам
*  Принимает путь до файлов, и ставит на них указатель
*  make_unique - умный указатель, если ссылка на него потеряется,
*                то файл будет закрыт автоматически
*  
*/
SyntaxAnalyzer::SyntaxAnalyzer(
    const std::string& input_file_path, 
    const std::string& output_file_path
){
    /* Логи */
    cout << "Запуск конструктора" <<                    endl;
    cout << "input_file_path - "  << input_file_path << endl;
    cout << "output_file_path - " << input_file_path << endl;

    file_input_ = (std::make_unique<std::ifstream>(input_file_path));
    file_output_ = (std::make_unique<std::ofstream>(output_file_path));
    translation_map_ = {
        {"var", "int"},
        /* Другие ликсемы ... */
    };
}


/* Чтение данных из входного файла, сохранение в буфер
*  Далее идет перевод 
*  В конце запись в выходной файл
*/
void SyntaxAnalyzer::analyze_and_translate() {
    /* Логи */
    cout << "Вызов analyze_and_translate" << endl;

    /* В данной реализации пока считавает сточку за строчкой */
    std::string input_code;
    if (file_input_->is_open()) {
        std::stringstream buffer;
        buffer << file_input_->rdbuf();
        input_code = buffer.str();
    }
    else {
        std::cerr << "Не удалось открыть входной файл." << std::endl;
        return;
    }

    /* Анализ и перевод */
    std::string translated_code = translate_words(input_code);

    /* Запись переведенного кода в выходной файл */
    if (file_output_->is_open()) {
        *file_output_ << translated_code;
    }
    else {
        std::cerr << "Не удалось открыть выходной файл." << std::endl;
    }
}


/* Метод перевода 
*  Принмается строка для перевода
*  На выходе переведеный код
*/
std::string SyntaxAnalyzer::translate_words(const std::string& code) {
    /* Логи */
    cout << "Вызов translate_words" <<         endl;
    cout << "Строка code: "         << code << endl;


    /* Реализация алгоитма перевода */
    /* Пример: заменяем слова согласно карте отображений */
    std::istringstream iss(code);
    std::string word;
    std::ostringstream translated_code;

    while (iss >> word) {
        translated_code << translation_map_[word] << " ";
    }

    return translated_code.str();
}

/* Гетеры сетеры епт */
const std::unordered_map<std::string, std::string>& SyntaxAnalyzer::get_translation_map() const {
    return translation_map_;
}

void SyntaxAnalyzer::set_translation_map(const std::unordered_map<std::string, std::string>& translation_map) {
    translation_map_ = translation_map;
}

/* Перегрузки негра */
std::ostream& operator<<(std::ostream& os, SyntaxAnalyzer& obj) {
    for (const auto& entry : obj.get_translation_map()) {
        os << entry.first << " -> " << entry.second << std::endl;
    }
    return os;
}