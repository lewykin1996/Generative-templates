#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include "sql_query_builder.h"

int main() {
	SqlSelectQueryBuilder query_builder;

	// Добавляем несколько столбцов
	query_builder.AddColumns({ "name", "phone", "email" });

	// Указываем таблицу
	query_builder.AddFrom("students");

	// Добавляем сразу несколько условий
	query_builder.AddWhere({
		{"id", "42"},
		{"name", "John"}
		});

	// Строим запрос
	std::string query = query_builder.BuildQuery();

	// Выводим результат
	std::cout << query << std::endl;

	// Проверяем правильность результата
	assert(query ==
		"SELECT name, phone, email FROM students "
		"WHERE id=42 AND name=John;");

	return 0;
}