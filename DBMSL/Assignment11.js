/*db.Products.insertMany([
   ...   {
   ...     product_id: 1,
   ...     product_name: "Laptop",
   ...     quantity: 10,
   ...     price: 1200
   ...   },
   ...   {
   ...     product_id: 2,
   ...     product_name: "Wireless Mouse",
   ...     quantity: 50,
   ...     price: 25
   ...   },
   ...   {
   ...     product_id: 3,
   ...     product_name: "Bluetooth Headphones",
   ...     quantity: 30,
   ...     price: 150
   ...   },
   ...   {
   ...     product_id: 4,
   ...     product_name: "Smartphone",
   ...     quantity: 20,
   ...     price: 800
   ...   },
   ...   {
   ...     product_id: 5,
   ...     product_name: "Monitor",
   ...     quantity: 15,
   ...     price: 300
   ...   }
   ... ]);
   */


   var mapFunction = function() {
           emit(this.product_id, this.quantity * this.price); // Emit product_id and total price (quantity * price)
    };
    var reduceFunction = function(productId, values) {
          return Array.sum(values); // Sum the values for each product_id
       };
      

-
db.orders.mapReduce(
   mapFunction,
   reduceFunction,
   { out: "price_per_prod" }
)

db.totalprices.find({});
/*
[
  { _id: 5, value: 4500 },
  { _id: 3, value: 4500 },
  { _id: 4, value: 16000 },
  { _id: 2, value: 1250 },
  { _id: 1, value: 12000 }
]*/

/* if we want the mapreduce to return for single product_id*/
var mapFunction = function() {
   if(this.product_id===2){
   emit(this.product_id, this.quantity * this.price); // Emit product_id and total price (quantity * price)
}};
var reduceFunction = function(productId, values) {
  return Array.sum(values); // Sum the values for each product_id
};
/*for array entries*/
 db.Items.insertMany([
...     {
...         category: "Electronics",
...         price: [80000, 56000, 2000, 15000, 30000, 120000, 45000, 67000, 52000, 39000]
...     },
...     {
...         category: "Furniture",
...         price: [25000, 18000, 35000, 42000, 15000, 27000, 49000, 32000]
...     },
...     {
...         category: "Clothing",
...         price: [2000, 3000, 1500, 2500, 4000, 3500, 1000, 1200, 2200]
...     },
...     {
...         category: "Books",
...         price: [500, 1500, 800, 200, 300, 600, 1000, 700]
...     }
... ]);
var mapFunction = function() {
    if (Array.isArray(this.price)) {
        this.price.forEach(price => emit(this.category, price));
    }
};

var reduceFunction = function(key, values) {
    var sum = 0;
    for (var i = 0; i < values.length; i++) {
        sum += values[i];
    }
    return sum / values.length; // Calculate average for each category
};

db.Items.mapReduce(
    mapFunction,
    reduceFunction,
    {
        out: "average_category_prices"
    }
);

/*using aggregation as mapreduce is depricated*/

db.Products.aggregate([{$group:{_id:"$product_name",total_price:{$sum:{$multiply:["$quantity","$price"]}}}}]);


db.Employee.aggregate([
   {
     $project: {
       product_name: 1,
       totalCost: { $multiply: ["$quantity", "$price"] } // Calculate total cost for each document
     }
   },
   {
     $group: {
       _id: "$product_name", // Group by product name
       totalCost: { $sum: "$totalCost" } // Sum the total cost for each product
     }
   }
 ]);
 
