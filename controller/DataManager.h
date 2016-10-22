class DataManager
{
	public:
		static DataManager& getInstance();

		/**
		 * out is an array
		 */
		void read(const std::string &filename, std::string &out);
		void read(const std::string &filename, std::string &out, bool lastline);

		/**
		 * append by new line if str doesn't exist
		 */
		void write(const std::string &finename, const std::string &str);

		/** 
		 * empty file
		 */
		void empty(const std::string &filename);

	private:
		DataManager();
		DataManager(const DataManager&);
		DataManager& operator=(const DataManager&);
		~DataManager();
};
