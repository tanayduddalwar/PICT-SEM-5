db.createCollection(Employee);
db.Employee.insertMany([{"fname":"ram","lname":"kumar","dept":"Consultant","salary":1200000}]);
/*{
  acknowledged: true,
  insertedIds: { '0': ObjectId('6713fb12de25b8570ffe6911') }
}*/
db.Employee.insertMany([
  ...     {"fname": "ram", "lname": "kumar", "dept": "Consultant", "salary": 1200000},
  ...     {"fname": "sita", "lname": "sharma", "dept": "HR", "salary": 850000},
  ...     {"fname": "gopal", "lname": "verma", "dept": "Finance", "salary": 950000},
  ...     {"fname": "krishna", "lname": "nair", "dept": "IT", "salary": 1300000},
  ...     {"fname": "laxmi", "lname": "iyer", "dept": "Marketing", "salary": 780000},
  ...     {"fname": "arjun", "lname": "singh", "dept": "Operations", "salary": 920000}
  ]);
  /*
  {
    acknowledged: true,
    insertedIds: {
      '0': ObjectId('6713fe6fde25b8570ffe6912'),
      '1': ObjectId('6713fe6fde25b8570ffe6913'),
      '2': ObjectId('6713fe6fde25b8570ffe6914'),
      '3': ObjectId('6713fe6fde25b8570ffe6915'),
      '4': ObjectId('6713fe6fde25b8570ffe6916'),
      '5': ObjectId('6713fe6fde25b8570ffe6917')
    }
  }*/


    db.Employee.find({});
    /*[
     
      {
        _id: ObjectId('6713fe6fde25b8570ffe6912'),
        fname: 'ram',
        lname: 'kumar',
        dept: 'Consultant',
        salary: 1200000
      },
      {
        _id: ObjectId('6713fe6fde25b8570ffe6913'),
        fname: 'sita',
        lname: 'sharma',
        dept: 'HR',
        salary: 850000
      },
      {
        _id: ObjectId('6713fe6fde25b8570ffe6914'),
        fname: 'gopal',
        lname: 'verma',
        dept: 'Finance',
        salary: 950000
      },
      {
        _id: ObjectId('6713fe6fde25b8570ffe6915'),
        fname: 'krishna',
        lname: 'nair',
        dept: 'IT',
        salary: 1300000
      },
      {
        _id: ObjectId('6713fe6fde25b8570ffe6916'),
        fname: 'laxmi',
        lname: 'iyer',
        dept: 'Marketing',
        salary: 780000
      },
      {
        _id: ObjectId('6713fe6fde25b8570ffe6917'),
        fname: 'arjun',
        lname: 'singh',
        dept: 'Operations',
        salary: 920000
      }
    ]*/    

  db.Employee.find({"fname":"gopal"})
    /*  [
        {
          _id: ObjectId('6713fe6fde25b8570ffe6914'),
          fname: 'gopal',
          lname: 'verma',
          dept: 'Finance',
          salary: 950000
        }
      ]*/
  db.Employee.find({"salary": {$gte: 1200000}});
        /*
        [
          
          {
            _id: ObjectId('6713fe6fde25b8570ffe6912'),
            fname: 'ram',
            lname: 'kumar',
            dept: 'Consultant',
            salary: 1200000
          },
          {
            _id: ObjectId('6713fe6fde25b8570ffe6915'),
            fname: 'krishna',
            lname: 'nair',
            dept: 'IT',
            salary: 1300000
          }
        ]*/
   db.Employee.updateOne({"fname":"laxmi"},{$set:{"salary":4510000}});
       /*   {
            acknowledged: true,
            insertedId: null,
            matchedCount: 1,
            modifiedCount: 1,
            upsertedCount: 0
          }*/
  db.Employee.find({$or:[{"fname":"laxmi"},{"dept":"IT"}]});
  /*        [
            {
              _id: ObjectId('6713fe6fde25b8570ffe6915'),
              fname: 'krishna',
              lname: 'nair',
              dept: 'IT',
              salary: 1300000
            },
            {
              _id: ObjectId('6713fe6fde25b8570ffe6916'),
              fname: 'laxmi',
              lname: 'iyer',
              dept: 'Marketing',
              salary: 780000
            }
          ]*/
   db.Employee.find({$and:[{"dept":"IT"},{"salary":{$gte:130000}}]});
  /*          [
              {
                _id: ObjectId('6713fe6fde25b8570ffe6915'),
                fname: 'krishna',
                lname: 'nair',
                dept: 'IT',
                salary: 1300000
              }
            ]*/

              db.Employee.deleteOne({"fname":"laxmi"},{$set:{"salary":4510000}});
             /* { acknowledged: true, deletedCount: 1 }*/

/* Array Manipulation operators

db.students.insertOne({"name":"Tanay","grades":[]});
{
  acknowledged: true,
  insertedId: ObjectId('6729f4df8db263be8dfe6917')
}
 db.students.updateOne({"name":"Tanay"},{$push:{"grades":45}});
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
db.students.updateOne({"name":"Tanay"},{$push:{"grades":74}});
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
 db.students.updateOne({"name":"Tanay"},{$push:{"grades":7}});
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
db.students.updateOne({"name":"Tanay"},{$push:{"grades":33}});
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
 db.students.updateOne({"name":"Tanay"},{$push:{"grades":89}});
{
  acknowledged: true,
  insertedId: null,
  matchedCount: 1,
  modifiedCount: 1,
  upsertedCount: 0
}
db.students.find({});
[
  {
    _id: ObjectId('6729f4df8db263be8dfe6917'),
    name: 'Tanay',
    grades: [ 45, 74, 7, 33, 89 ],
    grade: [ 45 ]
  }
