class DataManager
{
	public:

		enum ReadMode { 
			ALL, // whole file
			LASTONE, // the last one line
			LASTTWO  // the last two lines, for players creating, only two players
		};

		static DataManager& getInstance();

		/** 
		 * default set mode to ALL
		 */
		void read(const std::string &filename, std::string &out);

		/** 
		 * mode == LASTONE, out is json object string
		 * mode == LASTTWO || ALL, out is json array string
		 */
		void read(const std::string &filename, std::string &out, ReadMode mode);

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
