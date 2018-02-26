(function($) {
  var PROOFREAD_CLASS_NAME = 'workflow-needs-proofreading';
  var PROOFREAD_WRAPPER_CLASS_NAME = 'wrapper-workflow-needs-proofreading';

  CKEDITOR.plugins.add('drupal_proofread', {
    icons: 'proofread',
    init: function(editor) {
      editor.addCommand('toggleProofread', {
        exec: function(editor) {
          if (editor.getSelection()) {
            var selection = editor.getSelection();
            if (selection.getSelectedText() !== '') {
              var wrapper = new CKEDITOR.dom.element('span');
              wrapper.addClass(PROOFREAD_CLASS_NAME).addClass(PROOFREAD_WRAPPER_CLASS_NAME);
              wrapper.setAttributes({title: 'OBS'});
              wrapper.setText(selection.getSelectedText());
              editor.insertElement(wrapper);
            } else {
              var element = editor.getSelection().getStartElement();
              if (element) {
                if (element.hasClass(PROOFREAD_WRAPPER_CLASS_NAME)) {
                  // Replace proofread wrapper element with its content.
                  element.remove(true);
                } else {
                  if (element.hasClass(PROOFREAD_CLASS_NAME)) {
                    element.removeClass(PROOFREAD_CLASS_NAME);
                  } else {
                    element.addClass(PROOFREAD_CLASS_NAME);
                  }
                }
              }
            }
          }
        }
      });
      editor.ui.addButton('Proofread', {
        label: Drupal.t('Toogle Proofread'),
        command: 'toggleProofread',
      });
    }
  });
}(jQuery));
