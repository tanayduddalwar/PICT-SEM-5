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