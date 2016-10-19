#include <map>
#include <vector>

class Json
{
	public:

		enum Type { NIL, BOOLE, NUMBER, STRING, ARRAY, OBJECT };

		typedef std::vector<Json> array;
		typedef std::map<std::string, Json> object;

		/** Convert constructors */
		Json();
		explicit Json(int value);
		explicit Json(bool value);
		explicit Json(const array  &items);
		explicit Json(const object &objects);
		explicit Json(const std::string &value);

		/** Dump */
		void dump(std::string &out) const;
		void dump(int value, std::string &out) const;
		void dump(bool value, std::string &out) const;
		void dump(const object &values, std::string &out) const;
		void dump(const array  &values, std::string &out) const;
		void dump(const std::string &value, std::string &out) const;

		/** Overloads */
		const Json& operator[](size_t i);
		const Json& operator[](const std::string &key);
		friend std::ostream& operator<<(std::ostream &out, const Json &json);

		/** Accessors */ 
		Type type() const;
		int intValue() const;
		bool boolValue() const;
		array  arrayItems() const;
		object objectItems() const;
		std::string stringValue() const;

	private:
		int int_value;
		bool bool_value;
		Type json_type;
		array  array_items;
		object object_items;
		std::string string_value;
};

class JsonParser
{
	public:
		JsonParser(const std::string &jsonStr);

		Json parseJson();
		Json parseNumber();
		Json parseString();
		Json expect(const std::string &expected, Json result);

	private:
		void consumeWhitespace();
		char getNextToken();
		bool inRange(int x, int lower, int upper);

		size_t i;
		const std::string &str;
};
