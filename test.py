import logging
import requests
import json
import sqlite3

class DataManager:
    def __init__(self, db_path="data.db", log_file="app.log"):
        self.db_path = db_path
        self.log_file = log_file

    def fetch_data(self, url):
        try:
            response = requests.get(url)
            if response.status_code == 200:
                return response.json()
            else:
                logging.error(f"Failed to fetch data: {response.status_code}")
                return None
        except Exception as e:
            logging.error(f"Error fetching data: {e}")
            return None

    def save_to_json(self, data, filename="output.json"):
        try:
            with open(filename, "w") as f:
                json.dump(data, f, indent=4)
            logging.info(f"Data saved to {filename}")
        except Exception as e:
            logging.error(f"Error saving to file: {e}")

    def save_to_database(self, data):
        try:
            conn = sqlite3.connect(self.db_path)
            cursor = conn.cursor()
            cursor.execute("CREATE TABLE IF NOT EXISTS records (id INTEGER, name TEXT, value REAL)")
            for item in data:
                cursor.execute("INSERT INTO records VALUES (?, ?, ?)", (item["id"], item["name"], item["value"]))
            conn.commit()
            conn.close()
        except Exception as e:
            logging.error(f"Database error: {e}")

    def run(self, url):
        data = self.fetch_data(url)
        if data:
            self.save_to_json(data)
            self.save_to_database(data)
            logging.info("Data processing complete.")

# Example usage
if __name__ == "__main":
    manager = DataManager()
    manager.run("https://api.example.com/data")