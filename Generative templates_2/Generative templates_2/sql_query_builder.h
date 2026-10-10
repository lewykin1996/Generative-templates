#pragma once
#ifndef SQL_QUERY_BUILDER_H
#define SQL_QUERY_BUILDER_H

#include <string>
#include <vector>
#include <map>
#include <utility>

class SqlSelectQueryBuilder {
private:
	std::vector<std::string> columns;
	std::string table;
	std::vector<std::pair<std::string, std::string>> conditions;

public:
	// Добавление одного столбца
	SqlSelectQueryBuilder& AddColumn(const std::string& column) {
		columns.push_back(column);
		return *this;
	}

	// Добавление нескольких столбцов
	SqlSelectQueryBuilder& AddColumns(
		const std::vector<std::string>& new_columns
	) noexcept {
		columns.insert(
			columns.end(),
			new_columns.begin(),
			new_columns.end()
		);

		return *this;
	}

	// Установка названия таблицы
	SqlSelectQueryBuilder& AddFrom(const std::string& table_name) {
		table = table_name;
		return *this;
	}

	// Добавление одного условия
	SqlSelectQueryBuilder& AddWhere(
		const std::string& column,
		const std::string& value
	) {
		conditions.push_back({ column, value });
		return *this;
	}

	// Добавление нескольких условий
	SqlSelectQueryBuilder& AddWhere(
		const std::map<std::string, std::string>& kv
	) noexcept {
		for (const auto& item : kv) {
			conditions.push_back({ item.first, item.second });
		}

		return *this;
	}

	// Построение SQL-запроса
	std::string BuildQuery() const {
		std::string query = "SELECT ";

		// Если столбцы не заданы, выбираем все
		if (columns.empty()) {
			query += "*";
		}
		else {
			for (std::size_t i = 0; i < columns.size(); ++i) {
				if (i > 0) {
					query += ", ";
				}

				query += columns[i];
			}
		}

		// Добавляем таблицу
		if (!table.empty()) {
			query += " FROM " + table;
		}

		// Добавляем условия
		if (!conditions.empty()) {
			query += " WHERE ";

			for (std::size_t i = 0; i < conditions.size(); ++i) {
				if (i > 0) {
					query += " AND ";
				}

				query += conditions[i].first;
				query += "=";
				query += conditions[i].second;
			}
		}

		query += ";";

		return query;
	}
};

#endif