var today = new Date();

    var dd = today.getDate();
    /* adds 1 to month as satrts with 0 by default */
    var mm = today.getMonth()+1;

    var yyyy = today.getFullYear();
    
    /* adds 0 for single digits */
    if(dd < 10)
    {
        dd = "0" + dd;
    }

    if(mm < 10)
    {
        mm = "0" + mm;
    }

    /* prints output on js console */
    today = mm + "-" + dd + "-" + yyyy;
    console.log(today);

    today = mm + "/" + dd + "/" + yyyy;
    console.log(today);

    today = dd + "-" + mm + "-" + yyyy;
    console.log(today);

    today = dd + "/" + mm + "/" + yyyy;
    console.log(today);