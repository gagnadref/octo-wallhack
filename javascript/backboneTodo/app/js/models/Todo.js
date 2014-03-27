define(['backbone'], function(Backbone){ var Todo = Backbone.Model.extend({
  defaults: {
    title: "nothing",
	completed: false
  }
});
  return Todo;
});