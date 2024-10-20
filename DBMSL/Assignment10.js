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
db.Employee.aggregate([{$group:{_id:"$dept","totalsalary":{$sum:"$salary"},"employeecount":{$count:{}}}}]);
     /* [
        { _id: 'IT', totalsalary: 1300000, employeecount: 1 },
        { _id: 'Operations', totalsalary: 920000, employeecount: 1 },
        { _id: 'Marketing', totalsalary: 780000, employeecount: 1 },
        { _id: 'Finance', totalsalary: 950000, employeecount: 1 },
        { _id: 'HR', totalsalary: 850000, employeecount: 1 }
      ]*/

        db.Employee.aggregate([{$match:{"fname":"arjun"}}]);
    /*    [
          {
            _id: ObjectId('6713fe6fde25b8570ffe6917'),
            fname: 'arjun',
            lname: 'singh',
            dept: 'Operations',
            salary: 920000
          }
        ]*/    
       
  db.Employee.aggregate([{$group:{"_id":"$dept","avg":{$avg:"$salary"}}}]);
  /*        [
            { _id: 'IT', avg: 1300000 },
            { _id: 'Operations', avg: 920000 },
            { _id: 'Marketing', avg: 780000 },
            { _id: 'Finance', avg: 950000 },
            { _id: 'HR', avg: 850000 }
          ]      
            */
  db.Employee.aggregate([{$group:{"_id":"$null","avg":{$avg:"$salary"}}}]);
  /*[ { _id: null, avg: 960000 } ]*/
  
  
  db.Employee.aggregate([{$skip:2}]);
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
            },
            {
              _id: ObjectId('6713fe6fde25b8570ffe6917'),
              fname: 'arjun',
              lname: 'singh',
              dept: 'Operations',
              salary: 920000
            }
          ]*/

            
      db.Employee.createIndex({"fname":1,"dept":-1});  
      db.Employee.createIndex({"fname":1});
     /* fname_1*/
      db.Employee.find({"fname":"laxmi"}).hint("fname_1")
/*[
  {
    _id: ObjectId('6713fe6fde25b8570ffe6916'),
    fname: 'laxmi',
    lname: 'iyer',
    dept: 'Marketing',
    salary: 780000
  }
]*/