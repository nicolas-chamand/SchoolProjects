var updateTables;
$(document).ready(function() 
{
  var switched = false;
  updateTables = function() 
  {
    if (($(window).width() < 767) && !switched )
    {
      switched = true;
      $("table.responsive").each(function(i, element) 
      {
        splitTable($(element));
      });
      return true;
    }
    else if (switched && ($(window).width() >= 767)) 
    {
      switched = false;
      $("table.responsive").each(function(i, element) 
      {
        unsplitTable($(element));
      });
    }
  };
   
  $(document).ready(updateTables);
  $(window).on("redraw",function()
  {
    switched=false;
    updateTables();
  }); // An event to listen for
  $(window).on("resize", updateTables);
   
	
	function splitTable(original)
	{
		original.wrap("<div class='table-wrapper' />");
		
		var copy = original.clone();
		copy.find("td:not(:nth-child(2), :nth-child(1)), th:not(:nth-child(2), :nth-child(1))").css("display", "none");
		copy.removeClass("responsive");
		
		original.closest(".table-wrapper").append(copy);
		copy.wrap("<div class='pinned' />");
		original.wrap("<div class='scrollable' />");
    original.find("td:nth-child(2), th:nth-child(2)").css("display", "none");

    setCellHeights(original, copy);
	}
	
	function unsplitTable(original) 
  {
    original.closest(".table-wrapper").find(".pinned").remove();
    original.closest(".scrollable").find("td:nth-child(2), th:nth-child(2)").css("display", "");
    original.unwrap();
    original.unwrap();
	}

  function setCellHeights(original, copy) 
  {
    var tr = original.find('tr'),
        tr_copy = copy.find('tr'),
        heights = [];

    tr.each(function (index) 
    {
      var self = $(this),
          tx = self.find('th, td');

      tx.each(function () 
      {
        var height = $(this).innerHeight();
        heights[index] = heights[index] || 0;
        if (height > heights[index]) heights[index] = height;
      });
    });

    tr_copy.each(function (index) 
    {
      $(this).height(heights[index]);
    });
  }

});
