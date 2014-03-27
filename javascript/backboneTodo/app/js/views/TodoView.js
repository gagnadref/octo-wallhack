define(['backbone'], function(Backbone) {

var ENTER_KEYCODE = 13;

var createTitleInput = function createTitleInput(initialText) {
    var $input = $('<input type="text" data-selection></input>');
	$input.val(initialText);
	return $input;
};

var focusAndSelectAll = function ($input) {
	$input.focus();
	// select all text in the input
	$input[0].setSelectionRange(0, $input.val().length);
};

return Backbone.View.extend({
   tagName: 'li',
   template: _.template($("#todoView").html()),
   events: {
		'click span[data-selection]' : 'beginEdit',
		'blur input[data-selection]' : 'saveTodo',
		'keypress input[data-selection]' : 'handleEnterKeypress'
   },
   beginEdit: function beginEdit(event) {
		event.preventDefault();
		var $target = $(event.target);
		var currentText = $target.text();
		$target.remove();
		var $input = createTitleInput(currentText);
		this.$el.append($input);
		focusAndSelectAll($input);
   },
   saveTodo: function saveTodo(event){
   		event.preventDefault();
		var $target = $(event.target);
		var currentText = $target.val();
		this.model.set('title',currentText);
		this.render();
   },
   handleEnterKeypress: function handleEnterKeypress(event) {
		if(event.keyCode !== ENTER_KEYCODE) {
			return;
		}
		// if key pressed === Enter => saveTodo
		this.saveTodo(event);
   },
   render: function renderTodoView(){
		this.$el.html(this.template(this.model.toJSON()));
		return this;
   }
});
});