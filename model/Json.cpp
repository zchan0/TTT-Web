#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

#include "Json.h"

/*============================
=            Json            =
============================*/

Json::Json()
{
	json_type = NIL;
}

Json::Json(int value): int_value(value) 
{
	json_type = NUMBER;
}

Json::Json(bool value): bool_value(value)
{
	json_type = BOOLE; 
}

Json::Json(const std::string &value): string_value(value)
{
	json_type = STRING;
}

Json::Json(const array &items): array_items(items)
{
	json_type = ARRAY;
}

Json::Json(const object &objects): object_items(objects)
{
	json_type = OBJECT;
}

Json::Type Json::type() const
{
	return json_type;
}

int Json::intValue() const
{
	if (json_type == NUMBER)
		return int_value;
}

bool Json::boolValue() const
{
	return bool_value;
}

std::string Json::stringValue() const
{
	return string_value;
}

Json::array Json::arrayItems() const
{
	return array_items;
}

Json::object Json::objectItems() const
{
	return object_items;
}

const Json& Json::operator[] (size_t i)
{
	return array_items[i];
}

const Json& Json::operator[](const std::string &key) 
{
	return object_items[key];
}

std::ostream& operator<<(std::ostream &out, const Json &json)
{
	Json::Type type = json.type();
	switch(type) {
		case Json::NUMBER:
			out << json.intValue(); 
			break;
		case Json::STRING:
			out << json.stringValue();
			break;
		case Json::BOOLE:
			out << json.boolValue();
			break;
		case Json::NIL: case Json::ARRAY: case Json::OBJECT: 
		default:
			break;
	}
}

void Json::dump(int value, std::string &out) const
{
	char buf[32];
	snprintf(buf, sizeof buf, "%d", value);
	out += buf;
}

void Json::dump(bool value, std::string &out) const
{
	out += value ? "true" : "false";
}

void Json::dump(const std::string &value, std::string &out) const
{
	out += '"';
	for (size_t i = 0; i < value.length(); ++i) {
		const char ch = value[i];
		switch(ch) {
			case '\\':
				out += "\\\\"; break;
			case '"':
				out += "\\\""; break;
			case '\b':
				out += "\\b";  break;
			case '\f':
				out += "\\f";  break;
			case '\n':
				out += "\\n";  break;
			case '\r':
				out += "\\r";  break;
			case '\t':
				out += "\\t";  break;
			default:
				out += ch; 		 break;
		}
	}
	out += '"';
}

void Json::dump(const Json::object &values, std::string &out) const
{
	bool first = true;
	out += "{";
	for (Json::object::const_iterator it = values.begin(); it != values.end(); it++) {
		if (!first)
			out += ",";
		dump(it -> first, out);
		out += ": ";
		it -> second.dump(out);
		first = false;
	}
	out += "}";
}

void Json::dump(const Json::array &values, std::string &out) const
{
	bool first = true;
	out += "[";
	for (Json::array::const_iterator it = values.begin(); it != values.end(); it++) {
		if (!first)
			out += ", ";
		(*it).dump(out);
		first = false;
	}
	out += "]";
}

void Json::dump(std::string &out) const
{
	switch(json_type) {
		case Json::BOOLE:
			dump(bool_value, out);     break;
		case Json::NUMBER:
			dump(int_value, out);      break;
		case Json::STRING:
			dump(string_value, out);   break;
		case Json::ARRAY:
			dump(array_items, out);    break;
		case Json::OBJECT:
			dump(object_items, out); 	 break;
		case Json::NIL:
		default: 
			break;
	}
}

/*=====  End of Json  ======*/


/*=================================
=            JsonParse            =
=================================*/

JsonParser::JsonParser(const std::string &jsonStr): str(jsonStr), i(0)
{}

void JsonParser::consumeWhitespace()
{
	while(str[i] == ' ' || str[i] == '\r' || str[i] == '\t' || str[i] == '\n')
		i++;
}

char JsonParser::getNextToken()
{
	consumeWhitespace();
	
	if (i == str.size()) {
		throw "unexpected EOF";
	}

	return str[i++];
}

// Only integer now
Json JsonParser::parseNumber()
{
	try {
		size_t startPos = i;

		if (str[i] == '-') 
			i++;

		// start with 0 must be 0
		if (str[i] == '0') {
			i++;
			if (inRange(str[i], '1', '9')) {
				throw "leading 0s invalid number";
			}
		}
		// first digit from 1 ~ 9 and other digit could be any from  0 ~ 9
		else if (inRange(str[i], '1', '9')) {
			i++;
			while(inRange(str[i], '0', '9'))
				i++;
		}
		else {
			throw "invalid number";
		}

		return Json(std::atoi(str.c_str() + startPos));

	} catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

// Ignore escapes temporarily
Json JsonParser::parseString()
{
	std::string out;
	try {
		while (true) {
			if (i == str.size()) {
				throw "unexpected EOF";
			}

			char ch = str[i];	
			if (ch == '"') {
				++i;
				return Json(out);
			}

			out += ch;
			++i;
		}

	}	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

Json JsonParser::expect(const std::string &expected, Json result)
{
	--i;
	if (str.compare(i, expected.length(), expected) == 0) {
		i += expected.length();
		return result;
	} else {
		throw "parse error, expected " + expected + ", got " + str.substr(i, expected.length()); 
	}
}

Json JsonParser::parseJson()
{
	try {
		char ch = getNextToken();

		if (ch == '-' || inRange(ch, '0', '9')) {
			i--;
			return parseNumber();
		}

		if (ch == 't') 
			return expect("true", Json(true));

		if (ch == 'f')
			return expect("false", Json(false));

		if (ch == '"') 
			return parseString();

		if (ch == '{') {
			Json::object data;
			ch = getNextToken();
			if (ch == '}')
				return Json(data);

			while(true) {
				if (ch != '"') 
					throw "expected '\' in object";

				Json strres = parseString();
				std::string key = strres.stringValue();

				ch = getNextToken();
				if (ch != ':')
					throw "expected ':' in object";

				data[key] = parseJson();

				ch = getNextToken();
				if (ch == '}') 
					break;
				if (ch != ',')
					throw "expected ',' in object";

				ch = getNextToken();
			}
			return Json(data);
		}
		
		if (ch == '[') {
			Json::array data;
			ch = getNextToken();
			
			if (ch == ']')
				return Json(data);

			while(true) {
				i--;
				data.push_back(parseJson());
				ch = getNextToken();
				if (ch == ']')
					break;
				if (ch != ',')
					throw "expected ',' in array";

				ch = getNextToken();
				(void)ch;
			}

			return Json(data);
		}

	} catch (const char* msg) {
		std::cerr << msg << std::endl;
	}

}

/** Helpers */

bool JsonParser::inRange(int x, int lower, int upper)
{
	return (x >= lower && x <= upper);
}

/*=====  End of JsonParse  ======*/
