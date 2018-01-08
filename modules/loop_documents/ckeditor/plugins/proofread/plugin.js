(function($) {
  var PROOFREAD_CLASS_NAME = 'workflow-needs-proofreading';

  CKEDITOR.plugins.add('drupal_proofread', {
    icons: 'proofread',
    init: function(editor) {
      editor.addCommand('toggleProofread', {
        exec: function(editor) {
          if (editor.getSelection()) {
            var element = editor.getSelection().getStartElement();
            if (element) {
              if (element.hasClass(PROOFREAD_CLASS_NAME)) {
                element.removeClass(PROOFREAD_CLASS_NAME);
              } else {
                element.addClass(PROOFREAD_CLASS_NAME);
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
