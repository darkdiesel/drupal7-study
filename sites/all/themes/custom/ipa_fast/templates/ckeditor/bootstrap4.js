CKEDITOR.addTemplates('default', {
  // The name of sub folder which hold the shortcut preview images of the
  // templates.
  imagesPath: CKEDITOR.getUrl('/sites/all/themes/custom/ipa_fast/templates/ckeditor/images/'),

  // The templates definitions.
  templates: [
    {
      title: 'Row',
      image: 'template1.gif',
      description: 'add row',
      html: '<div class="row">[INSERT]</div>'
    },
    {
      title: 'Columns 6/6',
      image: 'template1.gif',
      description: 'Bootstrap columns',
      html: '<div class="col-lg-6 col-12">[INSERT]</div><div class="col-lg-6 col-12">[INSERT]</div>'
    },
    {
      title: 'Row with 2 columns',
      image: 'template1.gif',
      description: 'add row',
      html: '<div class="row"><div class="col-lg-6 col-12">[INSERT]</div><div class="col-lg-6 col-12">[INSERT]</div></div>'
    },
  ]
});
