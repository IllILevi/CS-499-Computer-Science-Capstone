from pymongo import MongoClient, errors
from bson.objectid import ObjectId

class animalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """

    def __init__(self, USER = 'aacuser',
                 PASS = 'SNHU1234',
                 HOST = 'localhost',
                 PORT = 27017,
                 DB = 'aac',
                 COL = 'animals'):
        try:
            self.client = MongoClient(f'mongodb://{USER}:{PASS}@{HOST}:{PORT}/?authSource=aac')
            self.database = self.client['%s' % (DB)]
            self.collection = self.database['%s' % (COL)]
        except errors.ConnectionFailure as e:
            raise Exception(f'Could not connect to MongoDB: {e}')

    def create(self, data):
        if data is not None:
            try:
                self.collection.insert_one(data)
                return True  # successful insert
            except Exception as e:
                raise Exception('Nothing to save, because data parameter is empty.')

    def read(self, query):
        if query is not None:
            try:
                cursor = self.collection.find(query)
                return list(cursor)
            except Exception as e:
                raise Exception(f'An error occurred: {e}')


    def update(self, query, updateData):
        if query and updateData is not None:
            try:
                cursor = self.collection.update_many(query, {'$set': updateData})
                print("Update successful!")
                print("Matched documents:", cursor.matched_count)
                print("Modified documents:", cursor.modified_count)
                print("Raw result:", cursor.raw_result)
                return cursor.modified_count
            except Exception as e:
                raise Exception("nothing to update")
        else:
            raise Exception("Invalid parameters")

    def delete(self, query):
        if query is not None:
            try:
                cursor = self.collection.delete_many(query)
                return cursor.deleted_count
            except Exception as e:
                raise Exception("nothing to delete")
        else:
            raise Exception("query parameter is empty")
