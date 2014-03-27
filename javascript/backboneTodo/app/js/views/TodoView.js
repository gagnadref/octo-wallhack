define(['backbone'], function(Backbone) {
return Backbone.View.extend({
   tagName: 'li',
   template: _.template($("#todoView").html()),
   render: function renderTodoView(){
		this.$el.html(this.template(this.model.toJSON()));
		return this;
   }
});
});