class DataManager
{
	public:
		static DataManager& getInstance();

		/**
		 * out is an array
		 */
		void read(const std::string &filename, std::string &out);

		/**
		 * append by new line
		 */
		void write(const std::string &finename, const std::string &str);

	private:
		DataManager();
		DataManager(const DataManager&);
		DataManager& operator=(const DataManager&);
		~DataManager();

};