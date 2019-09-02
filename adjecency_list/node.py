class Node(object):

    def __init__(self, data_x=None, data_y=None, next_node=None):
        self.data_x = data_x
        self.data_y = data_y
        self.next_node = next_node
    
    def get_data(self):
        return [self.data_x, self.data_y]
    
    def get_next(self):
        return self.next_node
    
    def set_next(self, new_next):
        self.next_node = new_next
